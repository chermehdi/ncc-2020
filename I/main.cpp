#include <bits/stdc++.h>

#define pb push_back
#define sz(u) (int)(u.size())

using namespace std;

const int MAXN = 2e5;

int n, q;
vector<vector<int>> g(MAXN);
vector<int> diam, par(MAXN), ans(MAXN, -1), downMost(MAXN), preDiam(MAXN),
    sufDiam(MAXN);
vector<bool> blocked(MAXN);
int furthestNode = -1, maxDist = -1, diamL = -1;

void furthest(int u, int pr, int d = 1) {
  par[u] = pr;
  if (d > maxDist) {
    maxDist = d;
    furthestNode = u;
  }
  for (int v : g[u]) {
    if (v == pr || blocked[v]) continue;
    furthest(v, u, d + 1);
  }
}

int findDiam(int u) {
  int A = -1, B = -1;
  maxDist = -1, furthestNode = -1;
  furthest(u, -1);
  A = furthestNode;
  if (diamL != -1) downMost[u] = maxDist;
  maxDist = -1, furthestNode = -1;
  furthest(A, -1);
  B = furthestNode;
  return B;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> q;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    g[u].pb(v);
    g[v].pb(u);
  }
  int curNode = findDiam(0);
  while (curNode != -1) {
    diam.pb(curNode);
    blocked[curNode] = 1;
    curNode = par[curNode];
  }
  diamL = maxDist;
  ans[diamL] = 0;
  ans[0] = diamL;
  for (int u : diam) {
    for (int v : g[u]) {
      if (blocked[v]) continue;
      findDiam(v);
      ans[maxDist] = max(diamL, ans[maxDist]);
      ans[diamL] = max(maxDist, ans[diamL]);
      downMost[u] = max(downMost[u], downMost[v]);
    }
  }
  preDiam[0] = 1, sufDiam[diamL - 1] = 1;
  for (int i = 1; i < diamL; i++)
    preDiam[i] = max(preDiam[i - 1], i + 1 + downMost[diam[i]]);
  for (int i = 1; i < diamL; i++)
    sufDiam[diamL - 1 - i] =
        max(sufDiam[diamL - i], i + 1 + downMost[diam[diamL - 1 - i]]);
  for (int i = 0; i < diamL - 1; i++)
    ans[preDiam[i]] = max(ans[preDiam[i]], sufDiam[i + 1]),
    ans[sufDiam[diamL - 1 - i]] =
        max(ans[sufDiam[diamL - 1 - i]], preDiam[diamL - 2 - i]);
  for (int i = diamL; i >= 0; i--) ans[i] = max(ans[i], ans[i + 1]);
  int l1, l2;
  while (q--) {
    cin >> l1 >> l2;
    if (ans[l1] >= l2)
      cout << "YES\n";
    else
      cout << "NO\n";
  }
  return 0;
}
