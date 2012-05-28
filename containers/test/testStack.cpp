#include<iostream>
#include<string>

#include "Stack.hpp"
using namespace containers;
int main()
{
#ifdef TEST_GENERIC_STACK
  try{
    Stack<int> is;
    Stack<std::string> ss;

    is.push(1);
    is.push(2);
    is.push(3);

    ss.push("name");
    ss.push("class");
    ss.push("id");

    std::cout<<"Int stack:"<<is;
    std::cout<<"String stack:"<<ss;

  }
  catch(std::exception const& ex){
    std::cerr<<"Exception: "<<ex.what()<<"\n";
    return -1;
  }
#endif
#ifdef TEST_STACK_SPECIALIZATION
  try{
    SmallStack<int,20> is;
    SmallStack<std::string,40> ss;

    is.push(1);
    is.push(2);
    is.push(3);

    std::cout<<"Num of elements= "<<is.size()<<"\n";
    std::cout<<"Top element= "<<is.top()<<"\n";
    std::cout<<"Top element= "<<is.pop()<<"\n";


    ss.push("name");
    ss.push("class");
    ss.push("id");
    std::cout<<"Num of elements= "<<ss.size()<<"\n";
    std::cout<<"Top element= "<<ss.top()<<"\n";
    std::cout<<"Top element= "<<ss.pop()<<"\n";
    std::cout<<"Top element= "<<ss.pop()<<"\n";
    std::cout<<"Top element= "<<ss.pop()<<"\n";

    std::cout<<"Int stack:"<<is;
    std::cout<<"String stack:"<<ss;

  }
  catch(std::exception const& ex){
    std::cerr<<"Exception: "<<ex.what()<<"\n";
    return -1;
  }

#endif
  return 0;
}
