#include<iostream>
#include<string>

#include "Queue.hpp"
using namespace containers;
int main()
{
#ifdef TEST_GENERIC_QUEUE
  try{
    Queue<int> is;
    Queue<std::string> ss;

    is.push(1);
    is.push(2);
    is.push(3);

    ss.push("name");
    ss.push("class");
    ss.push("id");

    std::cout<<"Int queue:"<<is;
    std::cout<<"String queue:"<<ss;

  }
  catch(std::exception const& ex){
    std::cerr<<"Exception: "<<ex.what()<<"\n";
    return -1;
  }
#endif
#ifdef TEST_QUEUE_SPECIALIZATION
  try{
    SmallQueue<int,5> is;
    SmallQueue<std::string,40> ss;

    is.push(1);
    is.push(2);
    is.push(3);
    is.push(4);
    is.push(5);

    std::cout<<"Num of elements= "<<is.size()<<"\n";
    std::cout<<"front element= "<<is.front()<<"\n";
    std::cout<<"front element= "<<is.pop()<<"\n";

    is.push(10);
    std::cout<<"Int queue:"<<is;

    std::cout<<"front element= "<<is.pop()<<"\n";
    std::cout<<"front element= "<<is.pop()<<"\n";
    std::cout<<"Int queue:"<<is;

    ss.push("name");
    ss.push("class");
    ss.push("id");
    std::cout<<"Num of elements= "<<ss.size()<<"\n";
    std::cout<<"front element= "<<ss.front()<<"\n";
    std::cout<<"front element= "<<ss.pop()<<"\n";
    std::cout<<"front element= "<<ss.pop()<<"\n";
    std::cout<<"front element= "<<ss.pop()<<"\n";

    std::cout<<"Int queue:"<<is;
    std::cout<<"String queue:"<<ss;

  }
  catch(std::exception const& ex){
    std::cerr<<"Exception: "<<ex.what()<<"\n";
    return -1;
  }

#endif
  return 0;
}
