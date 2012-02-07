// This file is distributed under the MIT License. See http://www.opensource.org/licenses/mit-license.php 
// for terms and conditions.
//
// Higher-order functions (HOFs) are functions that take other functions as their arguments. 
// A basic example of a HOF is map which takes a function and a list as its arguments, applies 
// the function to all elements of the list, and returns the list of its results. 
// For instance, we can write a function that subtracts 2 from all elements of 
// a list without using loops or recursion:

// subtractTwoFromList l = map (\x -> x - 2) l
//sample use case
//#include "hof.hpp"
//#include<iostream>
//#include<vector>
//using namespace fool;
//int main()
//{
//  std::vector<int> vi{1,2,3,4};
//  auto f = [](int& i){i+=2;};
//  FMap(f,vi);
//  for(auto v = vi.begin(); v != vi.end(); ++v)
//  {
//    std::cout<<*v<<"\t";
//  }
//  return 0;
//}
 

#include<algorithm>

//The typename function should be a function object
//The typename sequence should be a sequence type
namespace fool{
  template<typename function, typename sequence>
  sequence& FMap(function &f,sequence &s)
  {
    std::for_each(s.begin(),s.end(),
        [&f](typename sequence::value_type& v) {
          f(v);
        });
    return s;
  }

  template<typename function, typename sequence>
  inline sequence& FoF(function &f, sequence &s)
  {
    return FMap(f,FMap(f,s));
  }
}
