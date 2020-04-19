//
// Author MaxHeap
//
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

const int N = 200050;

int n, q;
vector<int> g[N];
vector<int> dist, par;
vector<bool> bad;
vector<int> deepest;
vector<int> from_left, from_right, from_left_d, from_right_d;

void dfs(int u, int p, int d = 0) {
  dist[u] = d;
  par[u] = p;
  for (int v : g[u]) {
    if (v == p) continue;
    dfs(v, u, d + 1);
  }
}

int dfs_furthest(int u, int p, int d = 0) {
  dist[u] = d;
  par[u] = p;
  int best = u;
  for (int v : g[u]) {
    if (v == p || bad[v]) continue;
    int k = dfs_furthest(v, u, d + 1);
    if (dist[k] > dist[best]) {
      best = k;
    }
  }
  return best;
}

int find_diameter_from(int u) {
  int furthest = dfs_furthest(u, 0);
  int r = dfs_furthest(furthest, 0);
  return dist[r] + 1;
}

vector<int> find_diameter() {
  dfs(1, 0);
  int furthest = 0;
  for (int i = 1; i <= n; ++i) {
    if (dist[furthest] < dist[i]) {
      furthest = i;
    }
  }

  dist.assign(n + 1, 0);
  par.assign(n + 1, 0);
  dfs(furthest, 0);

  furthest = 0;
  for (int i = 1; i <= n; ++i) {
    if (dist[furthest] < dist[i]) {
      furthest = i;
    }
  }
  vector<int> diameter;
  int u = furthest;
  while (u != 0) {
    diameter.push_back(u);
    u = par[u];
  }
  return diameter;
}

int deepest_node(int u, int p, int d = 1) {
  dist[u] = d;
  int ans = d;
  for (int v : g[u]) {
    if (v == p) continue;
    ans = max(deepest_node(v, u, d + 1), ans);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> q;
  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dist.assign(n + 1, 0);
  par.assign(n + 1, 0);

  vector<int> diameter = find_diameter();

  bad.assign(n + 1, false);
  fill(dist.begin(), dist.end(), 0);
  from_left.assign(n + 1, 0);
  from_left_d.assign(n + 1, 0);
  from_right_d.assign(n + 1, 0);
  from_right.assign(n + 1, 0);
  deepest.assign(n + 1, 0);

  int d = 0;
  for (int u : diameter) {
    bad[u] = true;
  }
  vector<int> max_deepest(n + 1, 0);
  vector<int> best(n + 1, 0);

  for (int u : diameter) {
    for (int v : g[u]) {
      if (bad[v]) continue;
      // deepest in term of the number of nodes, not the number of edges.
      deepest[v] = deepest_node(v, u);
      d = max(find_diameter_from(v), d);
      max_deepest[u] = max(max_deepest[u], deepest[v]);
    }
  }
  from_left[diameter[0]] = 1;
  from_left_d[diameter[0]] = 1;
  int l = diameter.size() - 1;
  from_right[diameter[l]] = 1;
  from_right_d[diameter[l]] = 1;

  for (int i = 1; i < diameter.size(); ++i) {
    int u = diameter[i], p = diameter[i - 1];
    from_left[u] = from_left[p] + 1;
    from_left_d[u] = max(from_left[u] + max_deepest[u], from_left_d[p]);
  }

  for (int i = l - 1; i >= 0; --i) {
    int u = diameter[i], p = diameter[i + 1];
    from_right[u] = from_right[p] + 1;
    from_right_d[u] = max(from_right[u] + max_deepest[u], from_right_d[p]);
  }

  for (int i = 0; i < diameter.size(); ++i) {
    int u = diameter[i];
    int to_right = i + 1 < diameter.size() ? from_right_d[diameter[i + 1]] : 0;
    best[from_left_d[u]] = max(best[from_left_d[u]], max(to_right, d));
  }

  for (int i = diameter.size() - 1; i >= 0; --i) {
    int u = diameter[i];
    int to_left = i - 1 >= 0 ? from_left_d[diameter[i - 1]] : 0;
    best[from_right_d[u]] = max(best[from_right_d[u]], max(to_left, d));
  }
  for (int i = diameter.size() - 1; i >= 1; --i) {
    best[i] = max(best[i + 1], best[i]);
  }
  while (q--) {
    int l, r;
    cin >> l >> r;
    bool found = false;
    if (r > diameter.size()) {
      cout << "NO" << endl;
      continue;
    }
    cout << (best[r] >= l || best[l] >= r ? "YES" : "NO") << endl;
  }
}

