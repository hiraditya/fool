
#include <iostream>
#include "Thread.hpp"

class Hello : public Thread{
  protected:
    virtual void* Run(void*);
};

void* Hello::Run(void* p)
{
  char* msg = (char*)p;
  for(int i = 0;i<10;++i){
    std::cout<<msg<<"\n";
    Sleep(200);
  }
  return NULL;
}



int main()
{
  Hello thread_english;

  Hello thread_french;

  Hello thread_german;
  char* he = "Hello english";
  char* hf = "Hello french";
  char* hg = "Hello german";

  thread_english.Start(he);
  thread_french.Start(hf);
  thread_german.Start(hg);

  thread_english.Wait();
  thread_french.Wait();
  thread_german.Wait();
  return 0;

}
