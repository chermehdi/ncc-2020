#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const long long INF = 1LL << 60;

struct Query {
  int start, end, value;
  long long cost() {
    return (end - start + 1) * 1LL * value;
  }
  bool operator<(const Query& rhs) const {
    pair<pair<int, int>, long long> a = {{start, end}, value};
    pair<pair<int, int>, long long> b = {{rhs.start, rhs.end}, rhs.value};
    return a < b;
  }
};


int main() {
  int n, m; cin >> n >> m;
  vector<Query> v(m);
  for(int i = 0; i < m; ++i) {
    cin >> v[i].start >> v[i].end >> v[i].value;
  }
  sort(v.begin(), v.end());

  vector<long long> dp(n + 1, INF);
  dp[0] = 0;
  for(Query &q: v) {
    int l = q.start, r = q.end; 
    long long cost = q.cost() + dp[l - 1];

    for(int j = l; j <= r; ++j) {
      dp[j] = min(cost, dp[j]);
    }
  }
  cout << (dp[n] >= INF ? -1: dp[n]) << endl;
}
