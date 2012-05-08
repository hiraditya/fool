#ifndef UTILS_VECTOR_HPP
#define UTILS_VECTOR_HPP

#include<vector>
#include<iostream>
namespace general_utilities{
  template<typename T>
  std::ostream& operator<<(std::ostream& os,const std::vector<T>& v)
  {
    for(typename std::vector<T>::const_iterator i = v.begin(); i!= v.end(); ++i){
      os<<*i;
      os<<"\n";
    }
    return os;
  }
}
#endif // UTILS_VECTOR_HPP