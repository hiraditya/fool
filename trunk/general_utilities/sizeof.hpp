#ifndef SIZEOF_DATATYPES_HPP
#define SIZEOF_DATATYPES_HPP
/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */


#include <iostream>
int sizeof_datatypes()
{
  std::cout << "Size of short is " << sizeof(short) << "\n";
  std::cout << "Size of int is " << sizeof(int) << "\n";
  std::cout << "Size of long is " << sizeof(long) << "\n";
  std::cout << "Size of float is " << sizeof(float) << "\n";
  std::cout << "Size of double is " << sizeof(double) << "\n";
  std::cout << "Size of long double is " << sizeof(long double) << "\n";
  std::cout << "Size of char is " << sizeof(char) << "\n";
  std::cout << "Size of bool is " << sizeof(bool) << "\n";
  return 0;
}

#endif // SIZEOF_DATATYPES_HPP
