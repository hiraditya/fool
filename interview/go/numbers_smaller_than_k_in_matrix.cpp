   Find how many numbers is smaller than given number K.

  0 2 4
  1 3 5
  2 4 6

int lower_bound(int *b, int sz; int K) {
  if (b[sz-1] > K)
        return -1;
  int l = 0;
  int r = sz;
  while (l < r) {
    mid = (l+r)/2;
    int el = b[mid];

    if (el <= K) {
        l = mid + 1;
    }
    else {
        r = mid;
    }
  return mid;
}


Nlog(N)

F(N) = 3 F(N/2) + O(N) < NlogN


int CountSmaller(int[][] matrix, int N, int K) {
  int num = 0;
  for(int i = 0; i < N; ++i) {
    int idx = lower_bound(&matrix[i][0], N, K);
    if (idx != -1) {
      num += idx;
    } else {
      num += N;
    }
  }
  return num;
}
