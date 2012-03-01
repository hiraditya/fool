#ifndef TRACK_MACRO_HPP
#define TRACK_MACRO_HPP
#include "map_utils.hpp"
#include "vector_utils.hpp"
#include "FunctionInfo.h"

#include "MacroScopeClassifier.h"
#include <clang/Frontend/CompilerInstance.h>

#include <clang/Basic/TokenKinds.h>

#include <clang/Lex/PPCallbacks.h>
#include <clang/Lex/Token.h>
#include <clang/Lex/Preprocessor.h>
#include <iostream>

using namespace general_utilities;

struct CollectedMacroInfo{
  int defined_line;
  std::vector<int> invoked_lines;
  PPOperation op;
  MacroCategory m_cat;
  CondCategory c_cat;
  MacroScopeCategory s_cat;
};

std::ostream& operator<<(std::ostream& os, const CollectedMacroInfo& cmi)
{
  os<<"::";
  os<<cmi.s_cat;
  os<<"  ";
  os<<cmi.op;os<<"  ";
  os<<cmi.m_cat;os<<"  ";
  os<<cmi.c_cat;os<<"  ";
  os<<cmi.defined_line;
  os<<"  ";
  os<<cmi.invoked_lines;
  os<<"  ";
  return os;
}
    
 // template<class Ch,class Tr> 
 // std::basic_ostream<Ch,Tr>& operator<<(std::basic_ostream<Ch,Tr>& s, const simple& obj);

namespace clang{
  class TrackMacro : public PPCallbacks
  {
    public:
    /// PPCallback
    void MacroExpands(const Token &MacroNameTok, const MacroInfo* MI,
        SourceRange Range)
    {
      //std::cout<<"Macro "<<MacroNameTok.getIdentifierInfo()->getNameStart()
      //         <<" has expanded here\n\t";
      //std::cout<<"Macro "<<tok::getTokenName(MacroNameTok.getKind())<< " has expanded here\n\t";
      /// testing if the macro is defined in the same file
      /// so that global macros can be skipped         
      if(sm->isFromMainFile(MI->getDefinitionLoc())) {
        //NOTE PresumedLoc can be modified by the LINE directive
        PresumedLoc presumed = sm->getPresumedLoc(Range.getBegin());
        MacroStat[MacroNameTok.getIdentifierInfo()->
        getNameStart()].invoked_lines.push_back(presumed.getLine());
      }
      //if(MacroIsLocal(Range.getBegin())) {
      /*  if(MI->isFunctionLike()){
          std::cout<<"The macro is function like\n";
        }
        if(MI->isObjectLike())
          std::cout<<"The macro is object like\n";
        if(MI->isVariadic())
          std::cout<<"The macro is variadic\n";
      }*/
    }
    /// PPCallback
    void MacroDefined(const Token &MacroNameTok, const MacroInfo* MI)
    {
      //if(MacroIsLocal(MI->getDefinitionLoc())) {
      CollectedMacroInfo cmi;  
      if(sm->isFromMainFile(MI->getDefinitionLoc())) {
        PresumedLoc presumed = sm->getPresumedLoc(MI->getDefinitionLoc());        
        /*std::cout<<"Macro "<<MacroNameTok.getIdentifierInfo()->getNameStart()
                 <<" is defined at line number: "
                 <<presumed.getLine()<<"\n";*/
       cmi.defined_line = presumed.getLine();
      //std::cout<<"Macro "<<tok::getTokenName(MacroNameTok.getKind())<<" is defined here\n\t";
        if(MI->isFunctionLike()){
          cmi.m_cat = MacroCategory::function_like;
          //std::cout<<"The macro is function like: ";
        }
        if(MI->isObjectLike()){
          cmi.m_cat = MacroCategory::object_like;
          //std::cout<<"The macro is object like\n";
        }
        if(MI->isVariadic()){
          cmi.m_cat = MacroCategory::variadic;
          //std::cout<<"The macro is variadic\n";
        }
       MacroStat[MacroNameTok.getIdentifierInfo()->getNameStart()] = cmi;        
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
      //std::cout<<"File name in TrackMacro set to: "<<file_name;
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
    void PrintStats()
    {
      //using namespace general_utilities;
      std::map<std::string,CollectedMacroInfo>::const_iterator i = MacroStat.begin();
      for(; i!= MacroStat.end(); ++i){
        std::cout<<i->first;
        std::cout<<"\t";
        std::cout<<i->second;
        std::cout<<"\n";
      }
      //std::cout<<MacroStat;
    }
    void VerifyMacroScopeFast(std::map<std::string, Info>const & FunctionInfo)
    {
      std::map<std::string, Info>::const_iterator fi = FunctionInfo.begin();
      std::map<std::string, CollectedMacroInfo>::iterator ms;
      std::map<int,int> FunctionDefinitionRange;
      std::map<int,int>::iterator fdri;
      for( ; fi != FunctionInfo.end(); ++fi)
      {
        FunctionDefinitionRange[(fi->second).start_line] = (fi->second).end_line;
      }
      ms = MacroStat.begin();
      for( ; ms != MacroStat.end(); ++ms){
        fdri = FunctionDefinitionRange.lower_bound((ms->second).defined_line);
        if(fdri != FunctionDefinitionRange.begin() && fdri != FunctionDefinitionRange.end()){
          --fdri;//we want the previous index to find the function scope
          std::cout<<"For macro: "<<ms->first<<" the range returned is: "
          << fdri->first<<"\t"<<fdri->second<<"\n";
          if((ms->second).defined_line < fdri->second){
            (ms->second).s_cat = MacroScopeCategory::inside_function;
            std::cout<<"Macro: "<<ms->first<<" is inside function\n";
          }
        }
      }
    }
    void VerifyMacroScope(std::map<std::string, Info>const & FunctionInfo)
    {
      std::map<std::string, Info>::const_iterator fi = FunctionInfo.begin();
      std::map<std::string, CollectedMacroInfo>::iterator ms;
      for( ; fi != FunctionInfo.end(); ++fi)
      {
        ms = MacroStat.begin();       
        for( ; ms != MacroStat.end(); ++ms){
          if((ms->second).defined_line > (fi->second).start_line
            && (ms->second).defined_line < (fi->second).end_line){
            (ms->second).s_cat = MacroScopeCategory::inside_function;
            std::cout<<"Macro: "<<ms->first<<" is inside function "<<fi->first<<"\n";
          }
        }
      }
    }

  private:

    std::string file_name;
    std::map<std::string, CollectedMacroInfo>MacroStat;
    const CompilerInstance *pci;
    SourceManager* sm;
  };
}
#endif //TRACK_MACRO_HPP