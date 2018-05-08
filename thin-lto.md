# Overview of thin lto

## ThinLTOCodeGenerator.cpp
  - crossModuleImport (Perform cross-module importing for the module identified by ModuleIdentifier, calls collectDefinedGVSummariesPerModule)
  - gatherImportedSummariesForModule (Compute the list of summaries needed for importing into module.)
  - ThinLTOCodeGenerator::run (Main driver for the thinlto)


Sequential steps followed by parallel codegen

## Sequential
  - linkCombinedIndex
  - computeDevirtualization

## Parallel
Optimizer and codegen

For each module
  - loadModuleFromBuffer
  - saveTempBitcode
  - get the import list for the module
  - ProcessThinLTOModule (the main process)


## ProcessThinLTOModule
  - promoteModule
  - thinLTOResolveWeakForLinkerModule
  - thinLTOInternalizeModule (run internalization based on summary analysis, change symbol visibility to preserve/drop)
  - crossImportIntoModule
  - optimizeModule

# Compute all the import and export for every module using the Index.
## FunctionImport.cpp
  - ComputeCrossModuleImport (Main driver function to import and export symbols based on `ModuleToDefinedGVSummaries`)
  - ComputeImportForModule (compute the list of imports as well as the list of "exports", calls `computeImportForFunction`)
  - computeImportForFunction (Compute the list of functions to import for a given caller, calls `computeImportForFunctionAlongEdge`. Marks all functions and globals it (the function) references as exported
to the outside if they are defined in the same source module)
  - computeImportForReferencedGlobals (Mark these imported functions and the symbols they reference in their source module as
exported from their source module. Inserts `VI.getGUID()` to `ExportLists`)

# Build index to be made available during the thin-lto stage
## ModuleSummaryAnalysis.cpp
  - buildModuleSummaryIndex (computes function summary, globals summary etc. calls `computeFunctionSummary`)
  - computeFunctionSummary (for each global `findRefEdges`, for each callsite in a function update `CallGraphEdges`, calls `addGlobalValueSummary` to attach function summary to `ModuleSummaryIndex`). If we want to add more summaries to a function we can update this function. For making other IPO passes perform cross-module thin-lto, this is the place where we can update summary.

## FunctionImport.cpp
  - Populate
    - ImportList to have the symbols available for use during thin-lto
    - ExportList to have the symbol available to the user during thin-lto
    - Relevant function:
      - doImportingForModule (imports relevant symbols for module M based on the module summary index, calls  renameModuleForThinLTO before calling Importer.importFunctions)
      - renameModuleForThinLTO (promotes globals if they are required to be imported by other module, calls processGlobalsForThinLTO to set the visibility)
      - FunctionImporter::importFunctions (import functions used by Module based on import list)


## ModuleSummaryIndex.cpp
Collect for each module the list of function it defines (GUID -> Summary).
  - collectDefinedGVSummariesPerModule (iterate over GlobalValueMap to populate summary of each GUID)
