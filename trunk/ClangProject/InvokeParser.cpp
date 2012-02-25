/***   CItutorial4.cpp   *****************************************************
 * This code is licensed under the New BSD license.
 * See LICENSE.txt for details.
 * 
 * The CI tutorials remake the original tutorials but using the
 * CompilerInstance object which has as one of its purpose to create commonly
 * used Clang types.
 *****************************************************************************/
#include "TrackMacro.hpp"

#include <iostream>

#include "llvm/Support/Host.h"

#include "clang/Frontend/CompilerInstance.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/LangOptions.h"
#include "clang/Parse/Parser.h"

/******************************************************************************
 *
 *****************************************************************************/
int main()
{
    using clang::CompilerInstance;
    using clang::TargetOptions;
    using clang::TargetInfo;
    using clang::FileEntry;
    using clang::Token;
    using clang::ASTContext;
    using clang::ASTConsumer;
    using clang::Parser;
    using clang::Preprocessor;
    
    CompilerInstance ci;
    ci.createDiagnostics(0,NULL);

    TargetOptions to;
    to.Triple = llvm::sys::getDefaultTargetTriple();
    TargetInfo *pti = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), to);
    ci.setTarget(pti);

    ci.createFileManager();
    ci.createSourceManager(ci.getFileManager());
    ci.createPreprocessor();
    ci.getPreprocessorOpts().UsePredefines = false;
    ASTConsumer *astConsumer = new ASTConsumer();
    ci.setASTConsumer(astConsumer);

    ci.createASTContext();
    ci.createSema(clang::TU_Complete, NULL);

  const FileEntry *pFile = ci.getFileManager().getFile("test.c");
    ci.getSourceManager().createMainFileID(pFile);
    ci.getPreprocessor().EnterMainSourceFile();
    ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(),
                                             &ci.getPreprocessor());
/// @brief putting a callback to the preprocessor instance 
    Preprocessor& PP = ci.getPreprocessor();
    using clang::TrackMacro;
    TrackMacro* track_macro = new TrackMacro;
    PP.addPPCallbacks(track_macro);
///    
    Parser parser(ci.getPreprocessor(), ci.getSema());
    parser.ParseTranslationUnit();
    ci.getDiagnosticClient().EndSourceFile();
    ci.getASTContext().Idents.PrintStats();

    return 0;
}