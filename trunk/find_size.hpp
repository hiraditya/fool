/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

#ifndef SEQUENCE_UTILS_FINDSIZE_HPP
#define SEQUENCE_UTILS_FINDSIZE_HPP

#include<cstdlib>

namespace sequence_utils
{

  template<typename sequence, size_t sz>
  size_t find_size(sequence (&c)[sz])
  {
    return sz;
  }

  template<typename sequence>
  size_t find_size(sequence const& s)
  { 
    return s.size();
  }

}
#endif //SEQUENCE_UTILS_FINDSIZE_HPP
