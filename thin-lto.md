Overview of thin lto

ThinLTOCodeGenerator::run

Sequential steps followed by parallel codegen

# Sequential
linkCombinedIndex

computeDevirtualization


# Parallel
optimizer and codegen

for each module
  loadModuleFromBuffer
  saveTempBitcode
  get the import list for the module
  ProcessThinLTOModule (the main process)
  
Actual import happens in crossImportIntoModule (called from ProcessThinLTOModule)
