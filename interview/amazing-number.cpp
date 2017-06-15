/*
Define amazing number as: its value is less than or equal to its index. Given a
circular array, find the starting position, such that the total number of
amazing numbers in the array is maximized.

Example 1: 0, 1, 2, 3
Ouptut: 0

When starting point at position 0, all the elements in the array are equal to
its index. So all the numbers are amazing number.

Example 2: 1, 0, 0
Output: 1

When starting point at position 1, the array becomes 0, 0, 1. All the elements
are amazing number.  If there are multiple positions, return the smallest one.

should get a solution with time complexity less than O(N^2)*/

// Returns the amount of shift such that number of amazing number is maximized.
int maximize_amazing_number(circular_array<int> &v) {
  int start = 0;
  int max_amz = 0;
  int shift = 0;
  while (start != v.size()) {
    int amazing = 0;
    for (int i = 0; i < v.size(); ++i) {
      int pos = i+start;
      if (v[pos] <= pos-start) {
        amazing++;
      }
    }
    if (max_amz < amazing) {
      max_amz = amazing;
      shift = start;
    }
    start++;
  }
  return shift;
}
