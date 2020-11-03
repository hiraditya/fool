/*A frog trying to cross the a river. There are many stones on the river. The frog can jump onto these stones. Each stone cost some amount of energy. The goal is the find the least energy the frog needs to cross the river.

The frog can only jump to 4 directions: up, down, left, right from a existing stone.

 

For example, for a matrix like below, the least energy is 5 (1+2+1+1)

Frog

0 0 1 0 7

0 1 2 1 1

1 3 0 1 9

Destination*/

typedef vector<pair<int,int>> vecpair;
typedef pair<int,int> point;
// Assuming a square matrix of size N.
// Time complexity N*(N-1)*N

vecpair validIndices(int r, int c, int N) {
  vecpair v;
  if (r+1 < N)
    v.push({r+1, c});
  if (c+1 < N)
    v.push({r, c+1});
  if (r-1 >= 0)
    v.push({r-1, c});
  if (c-1 >= 0)
    v.push({r, c-1});
return v;
}

// init = {0, 2}
int getCost(int M[][], int N, point init) {
  queue<pair<point, int>> q;
    for (int i = 0; i < N; ++i) { // 
     if (M[0][i] != 0) {
        q.push({{0,i}, M[0][i]};
        visited.insert({0,i});
      }
    }

    set<point> visited;
    //int cost = M[init.first][init.second];
    int min_cost = INT_MAX;
    //q.push({init, cost});  // {0,2}, 1
    // BFS
    while(!q.empty()){
    auto p = q.top();
        q.pop();
        auto pts = validIndices(p.first.first, p.first.second, N);
        int cost_so_far = p.second;
        for (auto p1 : pts) { // {2,2} // // {1,1}, {x0, x2}, {1,3}, {x2,x2} // {x2,x2} {2,1}
          if (M[p1.first][p1.second] !=0 && !visited.count(p1)) {
            visited.insert(p1);
            q.push({p1, M[p1.first][p1.second] + cost_so_far); // {{2,2},  3} // {{1,1}, 4}..{{1,3}, 4}, // {{2,1},7}
            if (p1.second == N-1 && (min_cost > M[p1.first][p1.second] + cost_so_far)) {
              min_cost = M[p1.first][p1.second] + cost_so_far; // 7
            }
          }
        }
    }
    return min_cost;
}

int energy(int M[][], int N) {
    int min_cost = INT_MAX;
  /*for (int i = 0; i < N; ++i) { // 
      if (M[0][i] != 0)
        curr_cost = getCost(M, N);
      if (curr_cost < min_cost)
        curr_cost = min_cost
    }*/

  return getCost(M, N);
}
