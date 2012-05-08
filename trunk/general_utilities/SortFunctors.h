#ifndef SORTFUNCTORS_H
#define SORTFUNCTORS_H

#include<string>
/*
bool SortString(std::string const& s1,std::string const& s2){
  return s1.compare(s2) < 0;
}
*/

struct SortString {
  bool operator()(std::string const& s1,std::string const& s2) const
  {
    return s1.compare(s2) < 0;
  }
};

#endif // SORTFUNCTORS_H
