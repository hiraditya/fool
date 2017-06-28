#include <ctime>
#include <iostream>
#include <chrono>
using namespace std;

long fibonacci(unsigned n)
{
    if (n < 2) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int c_style_time() {
  time_t t = time(0);   // get time now
  struct tm * now = localtime( & t );
  cout << (now->tm_year + 1900) << '-' 
    << (now->tm_mon + 1) << '-'
    << now->tm_mday
    << endl;
return 0;
}

int main() {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  std::cout << "f(42) = " << fibonacci(42) << '\n';
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end-start;
  std::time_t end_time = std::chrono::system_clock::to_time_t(end);

  std::cout << "finished computation at " << std::ctime(&end_time)
    << "elapsed time: " << elapsed_seconds.count() << "s\n";
}
