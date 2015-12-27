#include<fool/statistics/histogram.hpp>

#include<iostream>
#include<vector>

using namespace fool::statistics;
int main()
{
  std::vector<int> vi{1,2,3,4,1,2,3,3,10,3,4,5,5};
  histogram<int> h (vi);
  std::cout << "\nSize of vector: " << vi.size() << std::endl;
  std::cout << "\nPrinting the histogram\n";
  std::cout << h.print_hist(std::cout, true) << std::endl;
  std::cout << "\nPrinting the differential histogram\n";
  std::cout << h.print_differential(std::cout) << std::endl;
  std::cout << "\nPrinting the double differential histogram\n";
  std::cout << h.print_double_differential(std::cout) << std::endl;
  return 0;
}
