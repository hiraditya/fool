/* Write a time series class that stores and accesses double values based on
   time_t.  The class should be capable of storing up to the most recent 5000
   seconds of data.

You should provide the following functions:

class TimeSeries {
public:
  TimeSeries(size_t window);
  void AddValue(time_t current_time, double value);
  double GetValue(time_t desired_time);
};


The AddValue function will be called with monotonically increasing values of
current_time.  That is if AddValue is called for current_time = k, subsequent
calls will be for times >= k.  If there are multiple inserts for the same time_t
value, use the latest one.  If there were no inserts at a particular time,
GetValue should return the value which was inserted prior to that time.  For
example,

TimeSeries ts(5000);  // object saves the most recent 5000
                      // seconds
ts.AddValue(10, 2.0);
ts.AddValue(12, 3.0);
ts.AddValue(14, 3.5);
ts.GetValue(13)  // returns 3.0
ts.GetValue(14)  // returns 3.5
ts.GetValue(9)   // returns 0
ts.AddValue(5011, 4.0);
ts.GetValue(9)  // undefined -- more than 5000 seconds ago

Code will be evaluated by speed and design. Memory consumption is a secondary
concern and correctness is assumed.  The class should be as fast as possible
when the value is changed frequently or infrequently.

Final reminder: this class should be fast.
*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;


#include <time.h>
// Implement the class below.

class TimeSeries {
public:
  typedef std::pair<time_t, double> pair_t;
  void printq(std::deque<pair_t> &q) {
    for (auto i : q)
      std::cout << i.first << " " << i.second << '\n';
  }
  template<class ForwardIt, class T>
  ForwardIt binary_search(ForwardIt first, ForwardIt last, const T value)
  {
      ForwardIt it;
      int count, step;
      count = std::distance(first, last);
      while (count > 0) {
          it = first;
          step = count / 2;
          std::advance(it, step);
          if (it->first < value) {
              first = ++it;
              count -= step + 1;
          }
          else
              count = step;
      }
      return first;
  }

  TimeSeries(size_t window) : Max(window) {}
  void AddValue(time_t current_time, double value) {
    if (q.size() == Max)
      q.pop_front();
    std::pair<u_iterator, bool> ins = m.insert(std::make_pair(current_time, value));
    if (!ins.second) {
      // Already present => remove from the queue and add it to the end.
      u_iterator p = ins.first;
      p->second = value;
      q.back().second = value; // only the last can have current time.
    } else
      q.push_back(std::make_pair(current_time, value));
    //printq(q);
  }

  double GetValue(time_t dt) {
    u_iterator i = m.find(dt);
    if (i != m.end())
      return i->second;
    std::deque<pair_t>::iterator it = binary_search(q.begin(), q.end(), dt);
    if (it == q.begin()) // Previous values
      return 0;
    if (it != q.end())
      return (--it)->second;
    return 0;
  }
private:
   const size_t Max;
   std::deque<pair_t> q;
   typedef std::unordered_map<time_t, double> umap;
   typedef umap::iterator u_iterator;
   umap m;
};


// This function will be called in the final testcase
// so that you may evaluate your code with your own
// customized test function.  Note that stdout will be captured
// and put on the web page, so be careful about
// outputting too much data.
void test_function ( ) {
}

int main() {
  TimeSeries ts(5000);
  std::string line;
  std::string command;
  time_t t = 0;
  double v = 0.;
  while (getline(std::cin, line)) {
    std::stringstream strin(line);
    strin >> command;
    if (command == "ADD_VALUE") {
      strin >> t >> v;
      ts.AddValue(t, v);
    } else if (command == "GET_VALUE") {
      strin >> t;
      fprintf(stdout, "get %li : %.1f\n", t, ts.GetValue(t));
    } else if (command == "test_function") {
      test_function();
    }
  }
}
