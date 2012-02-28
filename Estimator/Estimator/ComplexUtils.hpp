/**
* @author Aditya Kumar
*
* Copyright (c) 2012 Texas A&M University
*
* This file is distributed under the MIT License.
* See http://www.opensource.org/licenses/mit-license.php for terms
* and conditions.
*/
#ifndef COMPLEX_UTILS_HPP
#define COMPLEX_UTILS_HPP
#include<complex>
#include<iostream>
#include<iomanip>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::complex<T> c)
{
  os<<'('<<c.real()<<","<<c.imag()<<')';
  return os;
}

#endif //COMPLEX_UTILS_HPP
