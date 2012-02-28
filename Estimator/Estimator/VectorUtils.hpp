/**
* @author Aditya Kumar
*
* Copyright (c) 2012 Texas A&M University
*
* This file is distributed under the MIT License.
* See http://www.opensource.org/licenses/mit-license.php for terms
* and conditions.
*/
#ifndef VECTORUTILS_HPP
#define VECTORUTILS_HPP

#include<vector>
#include<algorithm>
#include<iostream>

namespace std_container_utils {

  template<typename elem_type>
  std::pair<elem_type,elem_type>
  find_max(std::vector<elem_type> const& v)
  {
    elem_type min,max;
    min = v[0];
    max = v[0];
    for(typename std::vector<elem_type>::const_iterator i = v.begin();
        i!= v.end(); ++i)
    {
      if(min>*i)
        min = *i;
      if(max<*i)
        max = *i;
    }
    return std::pair<elem_type,elem_type>(min,max);
  }

  template<typename elem_type>
  std::ostream& operator<<(std::ostream& os,std::vector<elem_type> const& v)
  {
    for(typename std::vector<elem_type>::iterator i = v.begin(); i!= v.end(); ++i)
      os<<*i<<"\n";
    return os;
  }

}

#endif //VECTORUTILS_HPP
