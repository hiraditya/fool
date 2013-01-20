#include <fool/standard/cons.hpp>

#include<iostream>
#include<vector>

using namespace fool::standard;
int main()
{
  std::vector<int> vi{1,2,3,4};
  auto f = [](int& i){i+=2;};
  int first = car(vi);
  std::cout<<"\nfirst element is:"<<first;
  std::cout<<"\nthe cdr is:";
  auto last = cdr(vi);
  for(auto v = last.begin(); v != last.end(); ++v)
  {
    std::cout<<*v<<"\t";
  }
  std::cout<<"\nThe cons of two sequences are:";
  auto comb = cons(first,last);
  for(auto v = comb.begin(); v != comb.end(); ++v)
  {
    std::cout<<*v<<"\t";
  }

  std::vector<std::vector<int>> vov(5,vi);
  std::cout<<"\nThe original vector of vector:";
  for(auto v = vov.begin(); v != vov.end(); ++v)
  {
    for(auto e = v->begin(); e!=v->end();++e)
      std::cout<<*e<<"\t";
    std::cout<<"\n";
  }
  auto fof = caar(vov);
  std::cout<<"\nThe caar of vector of vector:"<<fof;
  std::cout<<"\nthe cdr of vector of vector:";
  auto cdr_vov = cdr(vov);
  for(auto v = cdr_vov.begin(); v != cdr_vov.end(); ++v)
  {
    for(auto e = v->begin(); e!=v->end();++e)
      std::cout<<*e<<"\t";
    std::cout<<"\n";
  }
 
  return 0;
}

