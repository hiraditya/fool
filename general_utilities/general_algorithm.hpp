#ifndef GENERAL_ALGORITHM_HPP
#define GENERAL_ALGORITHM_HPP
/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */
namespace general_utilities{

  template<typename T>
  inline unsigned int abs(const T& t) 
  {
    return t>0?t:-t;
  }


} //namespace general_utilities
#endif //GENERAL_ALGORITHM_HPP
