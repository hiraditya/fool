/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

// Higher-order functions (HOFs) are functions that take other functions as their arguments. 
// A basic example of a HOF is map which takes a function and a list as its arguments, applies 
// the function to all elements of the list, and returns the list of its results. 
// For instance, we can write a function that subtracts 2 from all elements of 
// a list without using loops or recursion:
// subtractTwoFromList l = map (\x -> x - 2) l

#include<fool/standard/exceptions.hpp>

#include<algorithm>
//The typename function should be a function object
//The typename sequence should be a sequence type
namespace fool {
  namespace standard 
  {
    /// \brief applies function (T function(T)) to each element 
    /// of the sequence<T>
    /// returns resulting sequence<T>
    /// This is the side effect free version
    template<typename function, typename sequence>
    struct FMap {
      sequence operator()(const function &f, const sequence &s) const
      {
        // enable_if sequence is of sequence type
          sequence seq;
          std::for_each(begin(s), end(s),
                        [f, &seq](typename sequence::value_type const & v) {
                             seq.push_back(f(v));
                        });
          return seq;
      }
    };

    template<typename function, typename sequence>
    inline auto map(const function& f, const sequence& s) ->
      decltype(FMap<function, sequence>()(f,s))
    {
      return FMap<function, sequence>()(f,s);
    }

    /// \brief apply function 'f' to sequence 's', and then 
    /// again apply the function on the result.
    /// returns resulting sequence.
    template<typename function, typename sequence>
    inline auto fof(const function &f, const sequence &s) ->
      decltype(FMap<function, sequence>()(f,s))
    {
      return FMap<function, sequence>()(f,FMap<function, sequence>()(f,s));
    }
  }
}
