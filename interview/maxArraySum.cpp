// Find the contiguous subarray within an array (containing at least one number)
// which has the largest sum.
#include<iostream>

int main() {
  const int length = 9;
  int A[length] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int newsum = A[0];
  int max = A[0];
  for(int i = 1; i < length; i++) {
    newsum = std::max(newsum+A[i], A[i]);
    max = std::max(max, newsum);
  }
  std::cout << "Max: " << max << "\n";
  return 0;
}
