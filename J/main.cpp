//
// Author MaxHeap
//
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <vector>
// BEGIN kratos/misc/constants.hpp

using std::vector;

namespace kratos {
const int INF_INT = 1 << 31;
const long long INF_LONG = 1LL << 60;
const vector<int> dx4 = {-1, 1, 0, 0};
const vector<int> dy4 = {0, 0, -1, 1};
};  // namespace kratos
// END kratos/misc/constants.hpp
// BEGIN kratos/graphs/flow.hpp
//
// Author Maxheap
//

using std::function;
using std::pair;
using std::queue;
using std::shared_ptr;
using std::vector;

namespace kratos {
template <class T = int>
struct FlowEdge {
  int to, rev;
  T cap, flow;

  static FlowEdge<T> Make(int to, int rev, T cap) {
    FlowEdge<T> edge = {to, rev, cap, 0};
    return edge;
  }
};

template <class T = int>
class FlowNetwork {
 private:
  int node_count;
  vector<vector<FlowEdge<T>>> g;
  vector<int> level;
  bool bfs(int s, int t);
  T dfs(vector<int> &next_edge, int s, int t, T cur_flow);

 public:
  FlowNetwork(int n);
  void add_edge(int u, int v, T capacity);
  T compute_flow(int s, int t);
  vector<bool> extract_min_cut();
};

template <class T>
FlowNetwork<T>::FlowNetwork(int n) : g(n), node_count(n), level(n) {}

template <class T>
void FlowNetwork<T>::add_edge(int u, int v, T capacity) {
  FlowEdge<T> e1 = {v, (int)g[v].size(), capacity, 0};
  FlowEdge<T> e2 = {u, (int)g[u].size(), 0, 0};
  g[u].push_back(e1);
  g[v].push_back(e2);
}

template <class T>
bool FlowNetwork<T>::bfs(int s, int t) {
  fill(level.begin(), level.end(), -1);
  level[s] = 0;
  vector<int> q(node_count);
  int qt = 0;
  q[qt++] = s;
  for (int qh = 0; qh < qt; qh++) {
    int cur_node = q[qh];
    for (FlowEdge<T> &e : g[cur_node]) {
      if (level[e.to] < 0 && e.cap - e.flow) {
        level[e.to] = level[cur_node] + 1;
        q[qt++] = e.to;
      }
    }
  }
  return level[t] >= 0;
}

template <class T>
T FlowNetwork<T>::dfs(vector<int> &next_edge, int u, int t, T cur_flow) {
  if (cur_flow == 0) return 0;
  if (u == t) return cur_flow;
  for (int &i = next_edge[u]; i < (int)g[u].size(); i++) {
    FlowEdge<T> &edge = g[u][i];
    if (edge.cap - edge.flow < 1) continue;
    int v = edge.to;
    if (level[v] == level[u] + 1) {
      T bottelneck =
          dfs(next_edge, v, t, std::min(cur_flow, edge.cap - edge.flow));
      if (bottelneck > 0) {
        edge.flow += bottelneck;
        g[edge.to][edge.rev].flow -= bottelneck;
        return bottelneck;
      }
    }
  }
  return static_cast<T>(0);
}

template <class T>
T FlowNetwork<T>::compute_flow(int s, int t) {
  T max_flow = 0;
  while (bfs(s, t)) {
    vector<int> next_edge(node_count);
    while (T bottelneck = dfs(next_edge, s, t, std::numeric_limits<T>::max())) {
      max_flow += bottelneck;
    }
  }
  return max_flow;
}

template <class T>
vector<bool> FlowNetwork<T>::extract_min_cut() {
  vector<bool> cut(node_count, false);
  for (int i = 0; i < node_count; ++i) {
    cut[i] = level[i] != -1;
  }
  return cut;
}
};  // namespace kratos

// END kratos/graphs/flow.hpp

using namespace std;

const int N = 505;

using kratos::FlowNetwork;

int n, m;
string grid[N];

// Computes the two nodes corresponding to single grid node.
// first element in the pair is the in_node.
// second element in the pair si the out_node.
pair<int, int> get_locations(int x, int y) {
  return make_pair(x * (m << 1) + (y << 1) + 1, x * (m << 1) + (y << 1) + 2);
}

// Returns true if the cell with coordinates (x, y) is safe.
bool is_safe(int x, int y) {
  return x >= 0 && x < n && y >= 0 && y < m && grid[x][y] != 'R';
}

// Add an edge from cell (i, j) to cell (x, y)
// This is done by linking the out of (i, j) to the in (x, y)
// And the reverse, linking the out of (x, y) to the in of (i, j)
// So that we have un bidirectional relation structure.
void link(int i, int j, int x, int y, FlowNetwork<int> &g) {
  auto u = get_locations(i, j);
  auto v = get_locations(x, y);
  g.add_edge(u.second, v.first, 1);
  g.add_edge(v.second, u.first, 1);
}

int main() {
  cin >> n >> m;

  int kids = 0, safe_points = 0;
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 'K') {
        ++kids;
      }
      if (grid[i][j] == 'G') {
        ++safe_points;
      }
    }
  }
  if (kids > safe_points) {
    cout << "No" << endl;
    return 0;
  }

  int source = 0, sink = n * (m << 1) + (m << 1) + 2;
  int size = sink + 1;
  FlowNetwork<int> g(size);

  // Link every cells from in -> out
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      auto u = get_locations(i, j);
      g.add_edge(u.first, u.second, 1);
    }
  }

  // Link possible cells
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] != 'R' || grid[i][j] == 'G') {
        for (int k = 0; k < 4; ++k) {
          int x = i + kratos::dx4[k];
          int y = j + kratos::dy4[k];
          if (is_safe(x, y)) {
            link(i, j, x, y, g);
          }
        }
      }
    }
  }

  // Link source and sink
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (grid[i][j] == 'K') {
        auto u = get_locations(i, j);
        g.add_edge(source, u.first, 1);
      } else if (grid[i][j] == 'G') {
        auto u = get_locations(i, j);
        g.add_edge(u.second, sink, 1);
      }
    }
  }

  int flow = g.compute_flow(source, sink);
  cout << (flow == kids ? "Yes" : "No") << endl;
}
