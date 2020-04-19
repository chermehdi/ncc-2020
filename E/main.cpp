
//
// Created by egor http://github.com/chermehdi/egor
// 
// @author MaxHeap

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;
const int N = 101000;

vector<int> a[N], b[N];
vector<pair<int, int>> dp;

pair<int, int> dfs(int u, int p) {
  if(dp[u].first != -1) {
    return dp[u];
  }
  int max_depth = 0;
  // (diameter, depth)
  pair<int, int> ans = {0, 0};
  for(int v: a[u]) {
    if(v == p) continue;
    pair<int, int> child_ans = dfs(v, u);
    if(!binary_search(b[u].begin(), b[u].end(), v)) {
      ans.first = max(ans.first, child_ans.first);
    }else {
      // part of the path
      ans.first = max({child_ans.first, child_ans.second + ans.second + 1, ans.first});
      ans.second = max(ans.second, child_ans.second + 1);
    }
  }
  return dp[u] = ans;
}

int main() {
  int n; cin >> n;
  dp.assign(n + 1, {-1, -1});
  for(int i = 2; i <= n; ++i) {
    int u = i, v; cin >> v;
    a[u].push_back(v);
    a[v].push_back(u);
  }
  for(int i = 2; i <= n; ++i) {
    int u = i, v; cin >> v;
    b[u].push_back(v);
    b[v].push_back(u);
  }

  for(int i = 1; i <= n; ++i) {
    sort(b[i].begin(), b[i].end());
  }

  auto ans = dfs(1, 0);
  cout << ans.first << endl;
}

