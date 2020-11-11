/*
program that generate a maze
starting point - end point
some point don't lead to an end
the path is not immediately obvious to the humans
complexity: path length, leaf nodes, sparsity
*/


enum Dir {
  Invalid = 0x0000,
  E = 0x0001,
  W = 0x0010,
  N = 0x0100,
  S = 0x1000
}

class Maze {
  char arr[N][N]; // Grid = xxxx
  Maze() {
    // Initialize arr = 0;
  }
  bool IsComplex() {
    // Count the path length,
    // Count the # leaf nodes
    // Count cycles
    return false;
  }

  vector<pair<int,int>> reachablePoints(int i, int j, int val) {
    // inspect the value if there is possible path to i,j
    vector<pair<int,int>> p;
    if (i < N-1)
      p.push_back({i+1, j});
    if (j < N-1)
      p.push_back({i, j+1});
    if (i > 0)
      p.push_back({i-1, j});
    if (j > 0)
      p.push_back({i, j-1});
    return p;
  }

  bool IsReachable() {
    // Depth first search to find end path
    int root = arr[0][0];
    stack<pair<int, int>> s;
    set<pair<int, int>> visited;
    s.push(root);
    while(!s.empty()) {
      auto p = s.top();
      // last point can be reached only by E, S
      if ((p.first == N-1 && p.second == N-2)) {
        if (arr[p.first][p.second] == 'E')
          return true;
      }
      if ((p.first == N-2 && p.second == N-1)) {
        if (arr[p.first][p.second] == 'S')
          return true;
      }
      s.pop();
      auto valid = reachablePoints(p.first, p.second);
      for (auto child : valid) {
        // 
        if (!visited.count(child))
          s.push(child);
      }
    }    
  }

  void generateMaze() {
    while (!complex) {
      int i = rand()/N;
      int j = rand()/N;
      int d = rand()/16;
      // account for invalid directions
      a[i][j] = d; // a[i][j] -> a[i][j+1]
      if (iter > threshold)
        break;
      else ++iter;
      // Complexity, and reachability analysis
      if (!Reachable() || !Complex())
        continue;
      
    }
  }
};
