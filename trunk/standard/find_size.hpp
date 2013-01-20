/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

#ifndef STANDARD_FINDSIZE_HPP
#define STANDARD_FINDSIZE_HPP

#include<cstdlib>
namespace fool {
  namespace standard
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
}
#endif // STANDARD_FINDSIZE_HPP
