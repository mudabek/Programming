#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
// using ll = long long;

struct Edge {
  int s;
  int t;
  int w;
};

const int NO_EDGE_VAL = 100000;
const int INF = 10000000;

void find_cycle(const vector<Edge>& edge_list, int n) {
  vector<vector<int>> d(n, vector<int>(n, INF));
  vector<vector<short>> next(n, vector<short>(n, -1));

  for (const auto& edge : edge_list) {
    int u = edge.s;
    int v = edge.t;
    int w = edge.w;
    d[u][v] = w;
    next[u][v] = v;
  }
  /*for (int v = 0; v < n; v++) {
    d[v][v] = 0;
    next[v][v] = v;
  }*/
  for (int i = 0; i < n; i++) {
    for (int u = 0; u < n; u++) {
      for (int v = 0; v < n; v++) {
        if (d[u][v] != INF && d[u][i] + d[i][v] < d[u][v]) {
          d[u][v] = max(-INF, d[u][i] + d[i][v]);
          next[u][v] = next[u][i];
        }
      }
    }
  }
  int x;
  for (x = 0; x < n; ++x) {
    if (d[x][x] < 0) {
      break;
    }
  }

  if (x == -1) {
    cout << "NO\n";
  } else {
    vector<int> ans;    
    int start = x;
    do {
      ans.push_back(x);
      x = next[x][start];
    } while (x != start);
    cout << "YES\n" << ans.size() << "\n";
    for (const auto& iter : ans) {
    cout << iter + 1 << " ";
    }    
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;
  int w;
  vector<Edge> edge_list;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> w;
      if (w != NO_EDGE_VAL) {
        edge_list.push_back({i, j, w});
      }
    }
  }
  /*edge_list.push_back({5, 1, -1});
  edge_list.push_back({1, 0, -1});
  edge_list.push_back({0, 5, -1});
  edge_list.push_back({0, 3, -1});
  edge_list.push_back({3, 2, -1});
  edge_list.push_back({2, 4, -1});
  edge_list.push_back({4, 3, -1});*/

  find_cycle(edge_list, n);
  return 0;
}