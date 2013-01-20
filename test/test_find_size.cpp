#include <fool/standard/find_size.hpp>
#include<iostream>
#include<vector>

using namespace fool::standard;
int main()
{
  std::vector<int> v{1,2,3,4,5};
  int a[6] = {0,1,2,3,4,5};
  std::cout<<"Size of vector: "<<find_size(v)<<"\tarray:"<<find_size(a);
  return 0;
}
