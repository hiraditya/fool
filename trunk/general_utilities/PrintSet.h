#ifndef PRINTSET_H
#define PRINTSET_H
#include<iostream>
#include<iterator>
#include<set>

// A helper function to simplify the main part.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& s)
{
    std::copy(s.begin(), s.end(), std::ostream_iterator<T>(std::cout, " "));
    return os;
}

#endif // PRINTSET_H
