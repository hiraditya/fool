#include<fool/statistics/histogram.hpp>

#include<fstream>
#include<iostream>
#include<iterator>
#include<vector>

using namespace fool::statistics;

template<typename T>
int test_print(histogram<T> &h)
{
  std::cout << "\nPrinting the histogram\n";
  std::cout << h.print_hist(std::cout, true) << std::endl;
  std::cout << "\nPrinting the differential histogram\n";
  std::cout << h.print_differential(std::cout, ',') << std::endl;
  std::cout << "\nPrinting the double differential histogram\n";
  std::cout << h.print_double_differential(std::cout, ',') << std::endl;
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
  assert (f.is_open());
  std::string str((std::istreambuf_iterator<char>(f)),
                  std::istreambuf_iterator<char>());
  //DEBUG (std::cout << "\nBefore: " << str);
  //str.erase(std::unique(str.begin(), str.end(),
  //                      [](char a, char b) {
  //                        return isspace(a) && isspace (b);
  //                      }),
  //          str.end());
  //DEBUG (std::cout << "\nAfter: " << str);
  std::vector<std::string> words;
  std::istringstream s (str);
  std::copy(std::istream_iterator<std::string>(s),
            std::istream_iterator<std::string>(),
            std::back_inserter(words));

  std::cout << "\nSize of vector: " << words.size() << std::endl;
  histogram<std::string> h(words);
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
