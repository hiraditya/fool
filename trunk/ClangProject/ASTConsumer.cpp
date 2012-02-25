#include "ASTConsumer.hpp"

int main(int argc, char** argv)
{
  if(argc<2){
    std::cerr<<"Usage: <file_name>";
    return -1;
  }
  CompilerInstance *pci = new CompilerInstance;
  MyASTConsumer astConsumer;
  astConsumer.Initialize(*pci);
  astConsumer.DumpContent(argv[1]);
  return 0;
}
