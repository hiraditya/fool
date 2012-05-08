#ifndef UTILS_COMPLEX_HPP
#define UTILS_COMPLEX_HPP

#include<complex>
#include<iostream>

#include<iomanip>
namespace general_utilities{
  template<typename T>
  std::ostream& operator<<(std::ostream& os, std::complex<T> c)
  {
    os<<'('<<c.real()<<","<<c.imag()<<')';
    return os;
  }
}

#endif // UTILS_COMPLEX_HPP