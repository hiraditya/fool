#ifndef UTILS_MAP_HPP
#define UTILS_MAP_HPP

#include<map>
#include<iostream>
namespace general_utilities{
  template<typename T1,typename T2>
  std::ostream& operator<<(std::ostream& os,const std::map<T1,T2>& m)
  {
    for(typename std::map<T1,T2>::const_iterator i = m.begin(); i!= m.end(); ++i){
      os<<i->first;
      os<<"\t";
      os<<i->second;
      os<<"\n";
    }
    return os;
  }
}
#endif // UTILS_MAP_HPP