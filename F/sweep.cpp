#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define ll long long
#define l first.first
#define r first.second
#define d second
using namespace std;
typedef pair<pair<int, int>, ll> node;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<node> v(m), ans;
  set<pair<ll, pair<int, int>>> ds;
  set<int> event;
  for (int i = 0; i < m; i++) {
    cin >> v[i].l >> v[i].r >> v[i].d;
    v[i].r++;
    event.insert(v[i].l);
    event.insert(v[i].r);
  }
  sort(v.begin(), v.end());
  auto x = v.begin();
  bool ok = 1;
  ans.push_back({{0, 0}, 0});
  if (v[0].l != 1)
    ok = 0;
  else
    for (auto i : event) {
      if (i == n + 1) break;
      while (x != v.end() && x->l <= i) {
        node tmp = {{0, x->l}, 0};
        auto y = lower_bound(ans.begin(), ans.end(), tmp,
                             [](node a, node b) -> bool { return a.r < b.r; });
//         if(ans.end() == y) {
  //         cerr << " for " << i << "-1" << endl;
        // }else {
          // cerr << y->l << " " << y->r << " " << y->d << endl;
        // }
        ll res = (y == ans.end() ? 0 : y->d);
        ds.insert({res + x->d * (ll)(-x->l + x->r), {x->l, x->r}});
        x++;
      }
      while (!ds.empty() && ds.begin()->second.second <= i)
        ds.erase(ds.begin());
      if (ds.empty()) {
        ok = 0;
        break;
      }
      if (ans.empty() || ans.back().r <= i)
        ans.push_back({{ds.begin()->second.first, ds.begin()->second.second},
                       ds.begin()->first});
      cerr << i << endl;
      for(auto t: ans) {
        cout << t.first.first << " " << t.first.second << " "  << t.second << endl;
      }
    }
  long long res = 1E18;
  for (auto x : ans) {
    if (x.r == n + 1) res = min(res, x.d);
  }
  if (!ok) res = -1;
  std::cout << res << endl;
}
