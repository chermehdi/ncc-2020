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
const int N = 1004000;
const long long INF = 1LL << 60;

long long seg[4 * N];

inline long long cost(pair<pair<int, int>, int> &val) {
  return (val.first.second - val.first.first + 1) * 1LL * val.second;
}


// returns true if b intersects with a [a0, b0, a1] 
bool intersect(const pair<pair<int, int>, int> &a, const pair<pair<int, int>, int> &b) {
  return a.first.first <= b.first.first && b.first.first - a.first.second <= 1;
}

void update(int root, int l, int r, int index, long long val) {
  if(l == r) {
    seg[root] = val;
    return;
  }
  int mid = (l + r) >> 1;
  if(index <= mid) {
    update(root << 1, l, mid, index, val);
  }else {
    update(root << 1 | 1, mid + 1, r, index, val);
  }
  seg[root] = min(seg[root << 1], seg[root << 1 | 1]);
}

long long query(int root, int l, int r, int a, int b) {
  if(l > b || r < a) {
    return INF;
  }
  if(a <= l && r <= b) {
    return seg[root];
  }
  int mid = (l + r) >> 1;
  long long left = query(root << 1, l, mid, a, b);
  long long right = query(root << 1 | 1, mid + 1, r, a, b);
  return min(left, right);
}

int main() {
  int n, m; cin >> n >> m;
  vector<pair<pair<int, int>, int>> v(m);
  vector<vector<pair<pair<int, int>, int>>> at(n + 1);

  for(int i = 0; i < m; ++i) {
    cin >> v[i].first.first >> v[i].first.second >> v[i].second;
    at[v[i].first.second].push_back(v[i]);
  }

  vector<long long> dp(n + 1, INF);
  fill(seg, seg + (N << 2), INF);

  update(1, 0, n, 0, 0);

  for(int i = 1; i <= n; ++i) {
    long long cur = INF;
    for(auto &pt: at[i]) {
      cur = min(query(1, 0, n, pt.first.first - 1, i) + cost(pt), cur);
    }
    dp[i] = min(cur, dp[i]);
    update(1, 0, n, i, dp[i]);
  }
  cout << (dp[n] == INF ? -1: dp[n]) << endl;
}

