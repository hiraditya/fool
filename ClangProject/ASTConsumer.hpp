#include <iostream>
#include <string>

#include "TrackMacro.hpp"
#include "llvm/Support/Host.h"

#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"

#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/Basic/SourceLocation.h"

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendOptions.h"
#include "clang/Frontend/Utils.h"


#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/HeaderSearch.h"

#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"

using clang::CompilerInstance;
using clang::TargetOptions;
using clang::TargetInfo;
using clang::FileEntry;
using clang::Token;
using clang::ASTContext;
using clang::ASTConsumer;
using clang::Parser;
using clang::Preprocessor;
using clang::SourceManager;
using clang::SourceLocation;
using clang::FunctionDecl;

/// from TrackMacro.hpp
using clang::TrackMacro;
/******************************************************************************
 *
 *****************************************************************************/
class MyASTConsumer : public clang::ASTConsumer
{
private:
    CompilerInstance *pci;
    MyASTConsumer *astConsumer;
    TrackMacro* track_macro;
    std::string current_file;

public:
    MyASTConsumer() : clang::ASTConsumer() 
    { 
      //CompilerInstance* pci = new CompilerInstance;
    }
    virtual ~MyASTConsumer() 
    { 
      //delete astConsumer;
      //delete track_macro;
    }

    virtual bool HandleTopLevelDecl(clang::DeclGroupRef d);
    int Initialize(CompilerInstance& ci);
    void DumpContent(std::string const& file_name);
    void PrintSourceLocation(FunctionDecl* fd);
    void PrintSourceLocation(SourceManager& sm, SourceLocation loc);
};

bool MyASTConsumer::HandleTopLevelDecl(clang::DeclGroupRef d)
{
  int count = 0;
  using namespace clang;
  //CompilerInstance& ci = *pci;
  DeclGroupRef::iterator it;
  for( it = d.begin(); it != d.end(); it++)
  {
    count++;
    VarDecl *vd = llvm::dyn_cast<clang::VarDecl>(*it);
    FunctionDecl *fd = llvm::dyn_cast<clang::FunctionDecl>(*it);
    if(fd){
      PrintSourceLocation(fd);
    }
/*    if(!vd)
    {
      std::cerr << "Not a variable decl: "<<vd<<"\n";
      continue;
    }
    std::cout << vd << std::endl;
    if( vd->isFileVarDecl() && vd->hasExternalStorage() )
    {
      std::cerr << "Read top-level variable decl: '";
      std::cerr << vd->getDeclName().getAsString();
      std::cerr << std::endl;
    }*/
  }
return true;
}

/******************************************************************************
 *
 *****************************************************************************/
int MyASTConsumer::Initialize(CompilerInstance& ci)
{
    pci = &ci;
//    if(ci.hasSema())
//      std::cout<<"Sema from start";
    ci.createDiagnostics(0,NULL);
    TargetOptions to;
    /// set the language to c++98
    ci.getInvocation().setLangDefaults(clang::InputKind::IK_CXX);

//    if(ci.getInvocation().getLangOpts()->CPlusPlus)
//      std::cout<<"c++ is defined now";
    
    to.Triple = llvm::sys::getDefaultTargetTriple();
    TargetInfo *pti = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), to);
    ci.setTarget(pti);
      
    ci.createFileManager();
//      if(ci.hasSema())
//      std::cout<<"Sema before source manager";
    ci.createSourceManager(ci.getFileManager());
    ci.createPreprocessor();
    
    using clang::PreprocessorOptions;
    using clang::HeaderSearchOptions;
    using clang::FrontendOptions;
    
    PreprocessorOptions& PPOpts = ci.getPreprocessorOpts();
    ///PPOpts.UsePredefines = false;
    Preprocessor& PP = ci.getPreprocessor();
    HeaderSearchOptions& HSOpts = ci.getHeaderSearchOpts();
    

/** 
 * \brief Adding the directory path for the compiler to search
 * AddPath (StringRef Path, frontend::IncludeDirGroup Group, 
 * bool IsUserSupplied, bool IsFramework, bool IgnoreSysRoot, 
 * bool IsInternal=false, bool ImplicitExternC=false)
*/  
/// General includes
    HSOpts.AddPath("/usr/include",
              clang::frontend::Angled,
              false,    false,    false);
    HSOpts.AddPath("/usr/include/linux",
              clang::frontend::Angled,
              false,    false,    false);
    HSOpts.AddPath("/usr/include/i386-linux-gnu",
              clang::frontend::Angled,
              false,    false,    false);

/// c++ includes    
    HSOpts.AddPath("/usr/include/c++/4.6",
              clang::frontend::Angled,
              false,    false,    false);
    HSOpts.AddPath("/usr/include/c++/4.6/tr1",
              clang::frontend::Angled,
              false,    false,    false);
/// c++ platform specific includes
    HSOpts.AddPath("/usr/include/c++/4.6/i686-linux-gnu",
              clang::frontend::Angled,
              false,    false,    false);
    HSOpts.AddPath("/usr/include/c++/4.6/i686-linux-gnu/64",
              clang::frontend::Angled,
              false,    false,    false);
    
/// gcc specific includes
    HSOpts.AddPath("/usr/lib/gcc/i686-linux-gnu/4.6.1",
              clang::frontend::Angled,
              false,    false,    false);
    
    FrontendOptions& FEOpts = ci.getFrontendOpts();

    PP.getBuiltinInfo().InitializeBuiltins(PP.getIdentifierTable(),
                                        PP.getLangOptions());
    clang::InitializePreprocessor(PP, PPOpts, HSOpts, FEOpts);
    //astConsumer = new MyASTConsumer();
    ci.setASTConsumer(this);

    ci.createASTContext();

/// pass the callback function    
    track_macro = new TrackMacro;
    PP.addPPCallbacks(track_macro);
///
    return 0;
}

void MyASTConsumer::DumpContent(std::string const& file_name)
{
  CompilerInstance& ci = *pci;
  current_file = file_name;
  const FileEntry *pFile = ci.getFileManager().getFile(file_name.c_str());
  ci.getSourceManager().createMainFileID(pFile);
  ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(),
                                            &ci.getPreprocessor());
  clang::ParseAST(ci.getPreprocessor(), this, ci.getASTContext());
  ci.getDiagnosticClient().EndSourceFile();
}

void MyASTConsumer::PrintSourceLocation(SourceManager& sm, SourceLocation loc)
{
  //  SourceLocation instantiation = sm.getInstantiationLoc(loc);
  //  SourceLocation spelling = sm.getSpellingLoc(loc);
#define PRINT_LOC(name, head) \
  do { \
    printf(head "%s  " #name ": {\n", indent.c_str()); \
    printf("%s    file: \"%s\",\n", indent.c_str(), \
      cgiEscape(sm.getBufferName(name)).c_str()); \
    pair<FileID, unsigned> lpair = sm.getDecomposedLoc(name); \
    printf("%s    line: %d,\n", indent.c_str(), \
      sm.getLineNumber(lpair.first, lpair.second)); \
    printf("%s    column: %d,\n", indent.c_str(), \
      sm.getColumnNumber(lpair.first, lpair.second)); \
    printf("%s  }", indent.c_str()); \
  } while(false)
/*  PRINT_LOC(instantiation, "");
  if (spelling != instantiation)
    PRINT_LOC(spelling, ",\n");*/
#undef PRINT_LOC

    clang::PresumedLoc presumed = sm.getPresumedLoc(loc);
//  if (presumed.getLine() != sm.getInstantiationLineNumber(loc)) {
//    printf(",\n%s  presumed: {\n", indent.c_str());
//    printf("%s    file: \"%s\",\n", indent.c_str(), presumed.getFilename());
    /// print only when the functions are in the current file
    if(current_file == presumed.getFilename()) {
      std::cout<<"line: "<<presumed.getLine();
      std::cout<<", column: "<<presumed.getColumn();
    }
//    printf("%s  }", indent.c_str());
//  }
//  printf("\n%s}", indent.c_str());
}

void MyASTConsumer::PrintSourceLocation(FunctionDecl* fd)
{
  using namespace clang;
  SourceManager& sm = pci->getSourceManager();  
  PresumedLoc presumed = sm.getPresumedLoc(fd->getSourceRange().getBegin());
    /// print only when the functions are in the current file
  if(current_file == presumed.getFilename()) {
    std::cout<<"Function declaration with name: "<<fd->getNameInfo().getAsString()<<"\n";
    //std::cout<<"\nCurrent file" << current_file;
    //std::cout<<"\nPresumed file"<<presumed.getFilename();
    std::cout<<"Start:\t";
    std::cout<<"line: "<<presumed.getLine();
    std::cout<<", column: "<<presumed.getColumn();
    presumed = sm.getPresumedLoc(fd->getSourceRange().getEnd());
    std::cout<<"\nEnd:\t";    
    std::cout<<"line: "<<presumed.getLine();
    std::cout<<", column: "<<presumed.getColumn();
  }
  std::cout<<"\n";  
}