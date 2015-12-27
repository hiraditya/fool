#ifndef HISTOGRAM_HPP
#define HISTOGRAM_HPP

/*
 *  @author Aditya Kumar 
 *
 *  This file is distributed under the MIT License. See 
 *  LICENCE.txt attached with this project or visit
 *  http://www.opensource.org/licenses/mit-license.php 
 *  for terms and conditions.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#include <general_utilities/vector_utils.hpp>
#include <general_utilities/map_utils.hpp>

using namespace general_utilities;
namespace fool {
namespace statistics {

/**
 * @class histogram
 * @brief useful for displaying different views of data from a set.
 */

template<typename T>
class histogram {

public:
  histogram()
  {}

  histogram(std::vector <T> &t)
    : vec (t)
  { }

  void read_data(std::istream &is) {
    assert (vec.empty() && "histogram is already initialized, use append.");
    T t;
    while (is >> t) {
      vec.push_back (t);
    }
  }

  /// Computes the histogram and puts in the \p hist
  void compute_histogram (std::map <T, unsigned> &hist) {
    for (unsigned i = 0; i < vec.size(); ++i) {
      hist[vec[i]]++;
    }
  }

  /// Computes the differential histogram and puts in the \p hist.
  /// Algorithm: Print side-by-side adjacent values in the form of a string
  /// and then sort the string.
  void compute_differential (std::map <std::string, unsigned> &hist) {
    assert (!vec.empty() && "Empty Histogram");
    for (unsigned i = 0; i < vec.size() - 1; ++i) {
      std::stringstream s;
      s << vec[i] << vec[i+1];
      hist[s.str()]++;
    }
  }

  /// Computes the double differential histogram and puts in the \p hist.
  /// Algorithm: Print side-by-side two adjacent values in the form of a string
  /// and then sort the string.
  void compute_double_differential (std::map <std::string, unsigned> &hist) {
    assert (!vec.empty() && "Empty Histogram");
    for (unsigned i = 0; i < vec.size() - 2; ++i) {
      std::stringstream s;
      s << vec[i] << vec[i+1] << vec[i+2];
      hist[s.str()]++;
    }
  }

  /// Prints the statistics of one entry at a time. This is the basic
  /// histogram. If \p sum is true, then add the elements as well.
  std::ostream& print_hist(std::ostream &os, bool sum=false) {
    if (!sum) {
      os << vec;
      return os;
    }

    std::map <T, unsigned> hist;
    compute_histogram (hist);
    os << hist;
    return os;
  }

  /// Prints the differential (delta) of the adjacent elements, side-by-side.
  /// This can be used to analyze the statistics of smallest sequence.
  /// Algorithm: Print side-by-side adjacent values in the form of a string
  /// and then sort the string.
  std::ostream& print_differential(std::ostream& os) {
    assert (!vec.empty() && "Empty Histogram");
    std::map <std::string, unsigned> hist;
    compute_differential (hist);
    os << hist;
    return os;
  }

  /// This will print two adjacent elements side-by-side so that
  /// next-next event can be analyzed.
  /// Algorithm: Print side-by-side two adjacent values in the form of a string
  /// and then sort the string.
  std::ostream& print_double_differential(std::ostream& os) {
    assert (!vec.empty() && "Empty Histogram");
    std::map <std::string, unsigned> hist;
    compute_double_differential (hist);
    os << hist;
    return os;
  }

  std::ostream& operator << (std::ostream &os) {
    os << vec;
    return os;
  }

private:
  std::vector <T> vec;
};
} // statistics
} // fool
#endif // HISTOGRAM_HPP

