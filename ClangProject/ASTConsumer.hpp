
#include "map_utils.hpp"
#include "FunctionInfo.h"
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
#include "clang/Frontend/LangStandard.h"

#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/HeaderSearch.h"

#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"

#include <iostream>
#include <string>

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
public:
    MyASTConsumer() : clang::ASTConsumer() 
    { 
      //CompilerInstance* pci = new CompilerInstance;
    }
    ~MyASTConsumer() 
    { 
      //delete track_macro;
      //track_macro=NULL;
    }

    virtual bool HandleTopLevelDecl(clang::DeclGroupRef d);
    int Initialize(CompilerInstance& ci);
    void DumpContent(std::string const& file_name);
    void PrintSourceLocation(FunctionDecl* fd);
    void PrintSourceLocation(SourceManager& sm, SourceLocation loc);
    void PrintStats();
    void VerifyMacroScope();

private:
    CompilerInstance *pci;
    MyASTConsumer *astConsumer;
    TrackMacro* track_macro;
    std::string current_file;
    std::map<std::string, Info> FunctionInfo;  
};

std::ostream& operator<<(std::ostream& os,const Info& inf)
{
  os<<inf.start_line;
  os<<"\t"<<inf.end_line;
  return os;
}
    
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
    /// can be extended for class declaration
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
    ci.getInvocation().setLangDefaults(clang::InputKind::IK_CXX, clang::LangStandard::lang_cxx11);

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
    HSOpts.AddPath("/media/space/opt_149739_build/lib/clang/3.1/include",
              clang::frontend::Angled,
              false,    false,    false);
    
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
/*    HSOpts.AddPath("/usr/lib/gcc/i686-linux-gnu/4.6.1/include",
              clang::frontend::Angled,
              false,    false,    false);
  */  
    FrontendOptions& FEOpts = ci.getFrontendOpts();

    PP.getBuiltinInfo().InitializeBuiltins(PP.getIdentifierTable(),
                                        PP.getLangOptions());
    clang::InitializePreprocessor(PP, PPOpts, HSOpts, FEOpts);
    //astConsumer = new MyASTConsumer();
    ci.setASTConsumer(this);

    ci.createASTContext();

/// pass the callback function    
    track_macro = new TrackMacro;
    track_macro->SetCompilerInstance(pci);
    PP.addPPCallbacks(track_macro);
///
    return 0;
}

void MyASTConsumer::DumpContent(std::string const& file_name)
{
  CompilerInstance& ci = *pci;
  current_file = file_name;

  //std::cout<<"Current file name in AST comsumer is: "<<current_file;
  const FileEntry *pFile = ci.getFileManager().getFile(file_name.c_str());
  ci.getSourceManager().createMainFileID(pFile);
  // set file and loc parameters for the track_macro callback
  // placing here is important. It should be after the source manager 
  // has created fileid for the file to be processed.
  track_macro->SetFileName(current_file);
  ///////////////////////////////////////////////////////////
  ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(),
                                            &ci.getPreprocessor());
  clang::ParseAST(ci.getPreprocessor(), this, ci.getASTContext());
  ci.getDiagnosticClient().EndSourceFile();
}

void MyASTConsumer::PrintSourceLocation(SourceManager& sm, SourceLocation loc)
{
    clang::PresumedLoc presumed = sm.getPresumedLoc(loc);
    /// print only when the functions are in the current file
    if(current_file == presumed.getFilename()) {
      std::cout<<"line: "<<presumed.getLine();
      std::cout<<", column: "<<presumed.getColumn();
    }
}

void MyASTConsumer::PrintSourceLocation(FunctionDecl* fd)
{
  using namespace clang;
  Info inf;
  SourceManager& sm = pci->getSourceManager();  
  PresumedLoc presumed = sm.getPresumedLoc(fd->getSourceRange().getBegin());
    /// print only when the functions are in the current file
  if(current_file == presumed.getFilename()) {
/*    std::cout<<"Function declaration with name: "<<fd->getNameInfo().getAsString()<<"\n";
    std::cout<<"Start:\t";
    std::cout<<"line: "<<presumed.getLine();
    std::cout<<", column: "<<presumed.getColumn();
    presumed = sm.getPresumedLoc(fd->getSourceRange().getEnd());
    std::cout<<"\nEnd:\t";    
    std::cout<<"line: "<<presumed.getLine();
    std::cout<<", column: "<<presumed.getColumn();*/
    inf.start_line = presumed.getLine();
    presumed = sm.getPresumedLoc(fd->getSourceRange().getEnd());
    inf.end_line = presumed.getLine();
    FunctionInfo[fd->getNameInfo().getAsString()] = inf;
  }
}

void MyASTConsumer::PrintStats()
{
  using namespace general_utilities;
  std::cout<<FunctionInfo;
  track_macro->PrintStats();
}

void MyASTConsumer::VerifyMacroScope()
{
  track_macro->VerifyMacroScope(FunctionInfo);
  track_macro->VerifyMacroScopeFast(FunctionInfo);
}
