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
  template<typename T1, T2>
  size_t abs(const T1 & t1) const
  {
    return t1 <0 ? -t1 : t1;
  }

  //returns the maximum of two
  template<typename T>
  const T& max(const T& t1, const T& t2) const
  {
    return t1 < t2 ? t2 : t1;
  }

} //namespace general_utilities



#endif //UTILS_ALGORITHM_HPP
