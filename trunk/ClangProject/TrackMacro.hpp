#ifndef TRACK_MACRO_HPP
#define TRACK_MACRO_HPP

#include <clang/Basic/TokenKinds.h>

#include <clang/Lex/PPCallbacks.h>
#include <clang/Lex/Token.h>
#include <clang/Lex/Preprocessor.h>
#include <iostream>

namespace clang{
  class TrackMacro : public PPCallbacks
  {
    public:

    void MacroExpands(const Token &MacroNameTok, const MacroInfo* MI,
        SourceRange Range)
    {
      std::cout<<"Macro "<<tok::getTokenName(MacroNameTok.getKind())<< " has expanded here\n\t";
      if(MI->isFunctionLike())
        std::cout<<"The macro is function like\n";
      if(MI->isObjectLike())
        std::cout<<"The macro is object like\n";
      if(MI->isVariadic())
        std::cout<<"The macro is variadic\n";
    }
    void MacroDefined(const Token &MacroNameTok, const MacroInfo* MI)
    {
      std::cout<<"Macro "<<tok::getTokenName(MacroNameTok.getKind())<<" is defined here\n\t";
      if(MI->isFunctionLike())
        std::cout<<"The macro is function like\n";
      if(MI->isObjectLike())
        std::cout<<"The macro is object like\n";
      if(MI->isVariadic())
        std::cout<<"The macro is variadic\n";
    }
    bool FileNotFound(StringRef FileName, SmallVectorImpl<char>& RecoveryPath)
    { 
      std::string path = "/usr/include";
      RecoveryPath.append(path.begin(),path.end());
/*      for(int i = 0; i<path.size(); ++i)
        RecoveryPath.push_back(path[i]);*/
      return true;
    }
  };
}
#endif //TRACK_MACRO_HPP