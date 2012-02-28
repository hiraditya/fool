#ifndef TRACK_MACRO_HPP
#define TRACK_MACRO_HPP

#include <clang/Frontend/CompilerInstance.h>

#include <clang/Basic/TokenKinds.h>

#include <clang/Lex/PPCallbacks.h>
#include <clang/Lex/Token.h>
#include <clang/Lex/Preprocessor.h>
#include <iostream>

namespace clang{
  class TrackMacro : public PPCallbacks
  {
    public:
    /// PPCallback
    void MacroExpands(const Token &MacroNameTok, const MacroInfo* MI,
        SourceRange Range)
    {
      std::cout<<"Macro "<<MacroNameTok.getIdentifierInfo()->getNameStart()
               <<" has expanded here\n\t";
      //std::cout<<"Macro "<<tok::getTokenName(MacroNameTok.getKind())<< " has expanded here\n\t";
      /// testing if the macro is defined in the same file
      /// so that global macros can be skipped         
      if(sm->isFromMainFile(MI->getDefinitionLoc())) {
      //if(MacroIsLocal(Range.getBegin())) {
        if(MI->isFunctionLike())
          std::cout<<"The macro is function like\n";
        if(MI->isObjectLike())
          std::cout<<"The macro is object like\n";
        if(MI->isVariadic())
          std::cout<<"The macro is variadic\n";
      }
    }
    /// PPCallback
    void MacroDefined(const Token &MacroNameTok, const MacroInfo* MI)
    {
      //if(MacroIsLocal(MI->getDefinitionLoc())) {
      if(sm->isFromMainFile(MI->getDefinitionLoc())) {
        PresumedLoc presumed = sm->getPresumedLoc(MI->getDefinitionLoc());        
        std::cout<<"Macro "<<MacroNameTok.getIdentifierInfo()->getNameStart()
                 <<" is defined at line number: "
                 <<presumed.getLine()<<"\n";
      //std::cout<<"Macro "<<tok::getTokenName(MacroNameTok.getKind())<<" is defined here\n\t";
        if(MI->isFunctionLike())
          std::cout<<"The macro is function like: ";
        if(MI->isObjectLike())
          std::cout<<"The macro is object like\n";
        if(MI->isVariadic())
          std::cout<<"The macro is variadic\n";
      }
    }
    /// PPCallback
    bool FileNotFound(StringRef FileName, SmallVectorImpl<char>& RecoveryPath)
    { 
      std::string path = "/usr/include";
      RecoveryPath.append(path.begin(),path.end());
/*      for(int i = 0; i<path.size(); ++i)
        RecoveryPath.push_back(path[i]);*/
      return true;
    }
    
    ///if the macro is local to the current file being processed
    bool MacroIsLocal(SourceLocation loc)
    {
      /// the source manager can decode the SourceLocation information
      //clang::FileID ID = sm->getFileID(loc);
      //std::cout<<"file id = "<<ID.getHashValue()<<"\n";
      //std::cout<<"Filea name is: "<<file_name;      
      if(file_name == sm->getBufferName(loc))
      //PresumedLoc presumed = sm->getPresumedLoc(loc);
      //if(file_name == presumed.getFilename())
        return true;
      return false;
    }
    
    void SetFileName(const std::string & f)
    {
      file_name = f;
      std::cout<<"File name in TrackMacro set to: "<<file_name;
      SetLocParams();
    }
    
    const std::string& GetFileName()
    {
      return file_name;
    }
    
    /// called everytime the file name is changed
    /// to get the file currently being processed
    void SetLocParams()
    {
      sm = &(pci->getSourceManager());
    }
    
    void SetCompilerInstance(const CompilerInstance* p)
    {
      pci = p;
    }
  private:
    std::string file_name;
    const CompilerInstance *pci;
    SourceManager* sm;
  };
}
#endif //TRACK_MACRO_HPP