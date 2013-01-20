#include <fool/standard/hof.hpp>
#include<iostream>
#include<vector>

using namespace fool::standard;
int main()
{
  std::vector<int> vi{1,2,3,4};
  auto f = [](int i){ return i+2; };
  std::vector<int> vo = fof(f,vi);
  for(auto i = vi.begin(), o = vo.begin(); i != vi.end(); ++i, ++o)
  {
    std::cout<<*i<<"\t";
    std::cout<<*o<<"\n";
  }
  return 0;
}

