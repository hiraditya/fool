#include<fool/statistics/histogram.hpp>

#include<fstream>
#include<iostream>
#include<iterator>
#include<vector>

using namespace fool::statistics;

template<typename T>
int test_print(const histogram<T> &h)
{
  std::cout << "\nPrinting the histogram\n";
  h.print_hist(std::cout, true);
  std::cout << "\nPrinting the differential histogram\n";
  h.print_differential(std::cout, ',');
  std::cout << "\nPrinting the double differential histogram\n";
  h.print_double_differential(std::cout, ',');
}

int test_int()
{
  std::vector<int> vi {1,2,3,4,1,2,3,3,10,3,4,5,5};
  std::cout << "\nSize of vector: " << vi.size() << std::endl;
  histogram<int> h(vi);
  test_print(h);
  return 0;
}

int test_string()
{
  std::vector<std::string> vi {
    "a", "b", "c", "d", "e",
    "a", "b", "c", "a", "b",
    "c", "d", "e", "d", "e",
    "a", "a", "b", "c", "d",
    "e", "b", "c", "d", "e",
  };
  std::cout << "\nSize of vector: " << vi.size() << std::endl;
  histogram<std::string> h(vi);
  test_print(h);
  return 0;
}

int test_file(const char* filename)
{
  std::ifstream f(filename);
  histogram<std::string> h;
  h.read_data(f);
  test_print(h);
  return 0;
}

int main()
{
  test_int();
  test_string();
  test_file("/home/hiraditya/work/fool/fool/test/statistics/test_file_for_histogram");
  return 0;
}
