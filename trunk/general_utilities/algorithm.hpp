#ifndef UTILS_ALGORITHM_HPP
#define UTILS_ALGORITHM_HPP

/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

namespace general_utilities{


  //returns the absolute value 
  template<typename T1, typename T2>
  size_t abs(const T1 & t1) 
  {
    return t1 <0 ? -t1 : t1;
  }

  //returns the maximum of two
  //if both have the same value then it returns the first one
  template<typename T>
  const T& max(const T& t1, const T& t2) 
  {
    return t1 < t2 ? t2 : t1;
  }

  //returns the minimum of two
  //if both have the same value then it returns the first one
  template<typename T>
  const T& min(const T& t1, const T& t2)
  {
    return t1 > t2 ? t2 : t1;
  }

  //the accumulator function returns the sum of all the elements
  //in the list
  template<typename T>
  inline T::size_type accum(const T* beg, const T* end)
  {
    T total = T();
    while(beg != end){
      total += *beg;
      ++beg;
    }
    return total;
  }

  //the accumulator function returns the sum of all the elements
  //in the sequence 
  template<typename T>
  inline T::size_type accum(const T& t)
  {
    T total = T();
    auto i = t.begin();

    while(i != t.end){
      total += *i;
      ++i;
    }

    return total;
  }
 



} //namespace general_utilities



#endif //UTILS_ALGORITHM_HPP
