#ifndef PRINTVECTOR_H
#define PRINTVECTOR_H

#include<iostream>
#include<vector>
#include<iterator>

// A helper function to simplify the main part.
template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<T>(os, "\n"));
    return os;
}

#endif // PRINTVECTOR_H
