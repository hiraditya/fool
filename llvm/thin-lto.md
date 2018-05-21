# Overview of thin lto

## Sequential steps followed by parallel codegen (`ThinLTOCodeGenerator::run()`)

### Sequential
  - linkCombinedIndex

### Parallel
  - Optimizer and codegen


# Overview of relevant files and functions

### ThinLTOCodeGenerator.cpp
For each module
  - ThinLTOCodeGenerator::run (Main driver for the thinlto calls `ProcessThinLTOModule`)
    - Sequential part calls:
      - linkCombinedIndex (Collects the information from all the indexes to create a single ModuleSummaryIndex. This should be populated for relevant information which we want to access during the thin-lto optimization phase) 
      - FunctionImport.cpp:ComputeCrossModuleImport (collect the import/export lists for all modules from the call-graph in the combined index, see below)
      - internalizeAndPromoteInIndex (Use global summary-based analysis to identify symbols that can be internalized)
    - Parallel part (optimizer + codegen):
      - loadModuleFromBuffer
      - saveTempBitcode
      - ProcessThinLTOModule (The main thin-lto optimizer process)
      - writeGeneratedObject
    - ProcessThinLTOModule calls these functions
      - promoteModule
      - thinLTOResolveWeakForLinkerModule
      - thinLTOInternalizeModule (run internalization based on summary analysis, change symbol visibility to preserve/drop)
      - crossImportIntoModule (imports function populated in ImportList for TheModule by calling `FunctionImporter::importFunctions`)
      - optimizeModule
  - crossModuleImport (Not interesting for thinlto. It is called by `llvm-lto.cpp` Perform cross-module importing for the module identified by `ModuleIdentifier`, calls `ModuleSummaryIndex::collectDefinedGVSummariesPerModule`, `FunctionImport::ComputeCrossModuleImport` and `crossImportIntoModule`)
  - gatherImportedSummariesForModule (Compute the list of summaries needed for importing into module, called by `llvm-lto.cpp`)

## Compute all the import and export for every module using the Index.
### FunctionImport.cpp
  - ComputeCrossModuleImport (Main driver function to import and export symbols based on `ModuleToDefinedGVSummaries`. Computes all the import and export for every module using the `ModuleSummaryIndex`. Calls `ComputeImportForModule`)
  - ComputeImportForModule (compute the list of imports as well as the list of "exports", calls `computeImportForFunction`)
  - computeImportForFunction (Compute the list of functions to import for a given caller. Marks all functions and globals it (the function) references as exported
to the outside if they are defined in the same source module)
  - computeImportForReferencedGlobals (Mark these imported functions and the symbols they reference in their source module as
exported from their source module. Inserts `VI.getGUID()` to `ExportLists`)

## Build index to be made available during the thin-lto stage
### ModuleSummaryAnalysis.cpp (builds a `ModuleSummaryIndex` object for each module, to be written to bitcode)
  - buildModuleSummaryIndex (computes function summary, globals summary etc. and save into index. Calls `computeFunctionSummary`. This is called by `ThinLTOBitcodeWriter.cpp:splitAndWriteThinLTOBitcode`)
  - computeFunctionSummary (for each global `findRefEdges`, for each callsite in a function update `CallGraphEdges`, calls `addGlobalValueSummary` to attach function summary to `ModuleSummaryIndex`). If we want to add more summaries to a function we can update this function. For making other IPO passes perform cross-module thin-lto, this is the place where we can update summary.

### FunctionImport.cpp
  - Populate
    - ImportList to have the symbols available for use during thin-lto
    - ExportList to have the symbol available to the user during thin-lto
    - Relevant function:
      - doImportingForModule (imports relevant symbols for module M based on the module summary index, calls  renameModuleForThinLTO before calling `Importer.importFunctions`)
      - renameModuleForThinLTO (promotes globals if they are required to be imported by other module, calls `processGlobalsForThinLTO` to set the visibility)
      - FunctionImporter::importFunctions (import functions used by Module based on import list)


### ModuleSummaryIndex.cpp
Collect for each module the list of function it defines (GUID -> Summary).
  - collectDefinedGVSummariesPerModule (iterate over `GlobalValueMap` to populate summary of each GUID)


### ThinLTOBitcodeWriter.cpp
  - WriteThinLTOBitcode is a bitcode writing module level pass that calls `writeThinLTOBitcode`
  - writeThinLTOBitcode (calls `splitAndWriteThinLTOBitcode`)
  - splitAndWriteThinLTOBitcode (split M into regular and thin LTO parts. calls `promoteTypeIds` `simplifyExternals`. Calls `buildModuleSummaryIndex` on the Module as well as on the Merged Module. Add ThinLTO flag to the merged module. Writes the module as well as merged module as bitcode.)


The summary is read by BitCodeReader
### BitCodeReader.cpp
  - parseModule(uint64_t ResumeBit, bool ShouldLazyLoadMetadata calls parseFunctionRecord:3306
  - parseModule() calls parseEntireSummary:4980
  - parseFunctionRecord
  - parseEntireSummary calls
