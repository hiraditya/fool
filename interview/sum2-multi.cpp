#include<iostream>
#include<array>

/**
   To find all pairs of numbers in an array whose sum is zero.
 */

// Returns the positions which sum to zero.
template<typename T>
// [b, e)
std::pair<T, T> find_sum2(T b, T e) {
  T p1 = b;
  T p2 = e;
  --p2; // Point to the last element of the range.
  while (p1 != p2) {
    int sum = *p1 + *p2;
    if (sum == 0)
      return {p1, p2};
    else if (sum < 0)
      ++p1;
    else // sum > 0
      --p2;
  }
  return {nullptr, nullptr};
}

int main() {
  // Sorted array.
  std::array<int, 9> a{ -4, -4, -1, 0, 1, 2, 3, 4, 4 };
  std::pair<int*, int*> v = find_sum2(a.begin(), a.end());
  auto b = a.begin();

  while (v.first != nullptr) {
    std::cout << "\nFound: " << *v.first << ", " << *v.second;
    std::cout << " Position: " << v.first -b << ", " << v.second -b;
    v = find_sum2(++v.first, v.second);
  }
  return 0;
}
