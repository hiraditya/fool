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
#include <fstream>
#include <iterator>
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

  histogram(std::vector<T> &t)
    : vec (t)
  { }

  histogram(std::vector<T> &t, std::vector<T> &i)
    : vec (t), ignore(i)
  { }

  // Reads the contents from file as a vector of words.
  // Returns true when successful.
  bool read_data(std::ifstream &is) {
    assert (vec.empty()
            && "histogram is already initialized, use append_hist.");
    assert (is.is_open());

    std::string str((std::istreambuf_iterator<char>(is)),
                    std::istreambuf_iterator<char>());

    str.erase(std::unique(str.begin(), str.end(),
                          [](char a, char b) {
                            return isspace(a) && isspace (b);
                          }), str.end());

    std::istringstream s(str);

    std::copy(std::istream_iterator<std::string>(s),
              std::istream_iterator<std::string>(),
              std::back_inserter(vec));
    return true;
  }

  void append_hist(const T& t) {
    vec.push_back(t);
  }

  void append_ignore(const T& t) {
    ignore.push_back(t);
  }

  void set_hist(std::vector<T> &v) {
    vec = v;
  }

  void set_ignore(std::vector<T> &i) {
    ignore = i;
  }

  void clear_hist() {
    vec.clear();
  }

  void clear_ignore() {
    ignore.clear();
  }

  /// Returns true if the arguments are in the ignore list.
  bool is_ignore(const T& t) const {
    if (std::find(ignore.begin(), ignore.end(), t) != ignore.end()) {
      return true;
    }
    return false;
  }

  /// Computes the histogram and puts in the \p hist
  void compute_histogram(std::map<T, unsigned> &hist) const {
    for (unsigned i = 0; i < vec.size(); ++i) {
      hist[vec[i]]++;
    }
  }

  /// Computes the differential histogram and puts in the \p hist.
  /// \p sep is the separator to be used while printing successive elements.
  /// Algorithm: Print side-by-side adjacent values in the form of a string
  /// and then sort the string.
  void compute_differential(std::map<std::string, unsigned> &hist,
                            char sep) const {
    assert (!vec.empty() && "Empty Histogram");
    for (unsigned i = 0; i < vec.size() - 1; ++i) {
      // Ignore the entries which are in the ignore list.
      if (is_ignore(vec[i]) || is_ignore(vec[i+1]))
        continue;

      std::stringstream s;
      s << vec[i] << sep << vec[i+1];
      hist[s.str()]++;
    }
  }

  /// Computes the double differential histogram and puts in the \p hist.
  /// \p sep is the separator to be used while printing successive elements.
  /// Algorithm: Print side-by-side two adjacent values in the form of a string
  /// and then sort the string.
  void compute_double_differential(std::map<std::string, unsigned> &hist,
                                   char sep) const {
    assert (!vec.empty() && "Empty Histogram");
    for (unsigned i = 0; i < vec.size() - 2; ++i) {
      // Ignore the entries which are in the ignore list.
      if (is_ignore(vec[i]) || is_ignore(vec[i+1]) || is_ignore(vec[i+2]))
        continue;

      std::stringstream s;
      s << vec[i] << sep << vec[i+1] << sep << vec[i+2];
      hist[s.str()]++;
    }
  }

  /// Prints the statistics of one entry at a time. This is the basic
  /// histogram. If \p sum is true, then add the elements as well.
  void print_hist(std::ostream &os, bool sum=false) const {
    if (!sum) {
      os << vec;
    }

    std::map<T, unsigned> hist;
    compute_histogram (hist);
    os << hist << "\nSize of hist: " << hist.size() << std::endl;
  }

  /// Prints the differential (delta) of the adjacent elements, side-by-side.
  /// This can be used to analyze the statistics of smallest sequence.
  /// \p sep is the separator to be used while printing successive elements.
  /// Algorithm: Print side-by-side adjacent values in the form of a string
  /// and then sort the string.
  void print_differential(std::ostream &os, char sep = ' ') const {
    assert (!vec.empty() && "Empty Histogram");
    std::map<std::string, unsigned> hist;
    compute_differential (hist, sep);
    os << hist;
  }

  /// This will print two adjacent elements side-by-side so that
  /// next-next event can be analyzed.
  /// \p sep is the separator to be used while printing successive elements.
  /// Algorithm: Print side-by-side two adjacent values in the form of a string
  /// and then sort the string.
  void print_double_differential(std::ostream &os, char sep = ' ') const {
    assert (!vec.empty() && "Empty Histogram");
    std::map<std::string, unsigned> hist;
    compute_double_differential (hist, sep);
    os << hist;
  }

  std::ostream& operator<<(std::ostream &os) const {
    os << vec;
    return os;
  }

private:
  std::vector<T> vec;
  // The ignore lists act as markers for computing the histogram.  These are
  // mainly useful when multiple lists are merged into vec.  Entries before
  // and after markers are considered as separate lists.
  std::vector<T> ignore;
};
} // statistics
} // fool
#endif // HISTOGRAM_HPP

