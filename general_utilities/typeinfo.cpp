#include<typeinfo>
#include<string>
#include<cxxabi.h>
#include<cstring>
#include<iostream>

template<typename> struct type_name { };

template <typename T>
std::string typestr()
{
#if defined(__GNUC__)
  std::size_t const BUFSIZE = 8192;
  std::size_t n = BUFSIZE;
  char buf[BUFSIZE];
  abi::__cxa_demangle(typeid(type_name<T>).name(), buf, &n, 0);
  return std::string(buf, ::strlen(buf));
#endif
}

template <typename T>
inline std::string typestr(T const&)
{ return typestr<T>(); }


int main()
{
  struct X {};
  std::string s = typestr(X());
  std::cout<<"Type of X is:"<<s;
}
