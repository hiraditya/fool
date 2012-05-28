#ifndef UTILS_SET_HPP
#define UTILS_SET_HPP
#include<iostream>
#include<iterator>
#include<set>

namespace general_utilities{
  // A helper function to simplify the main part.
  template<class T>
  std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
  {
      std::copy(s.begin(), s.end(), std::ostream_iterator<T>(std::cout, "\n"));
      return os;
  }
}
#endif // PRINTSET_H
