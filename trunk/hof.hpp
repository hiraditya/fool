// Higher-order functions (HOFs) are functions that take other functions as their arguments. 
// A basic example of a HOF is map which takes a function and a list as its arguments, applies 
// the function to all elements of the list, and returns the list of its results. 
// For instance, we can write a function that subtracts 2 from all elements of 
// a list without using loops or recursion:

// subtractTwoFromList l = map (\x -> x - 2) l
// 
// 

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
}
