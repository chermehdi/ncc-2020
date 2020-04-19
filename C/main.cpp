//
// Author MaxHeap
//
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
  int n, k; cin >> n >> k;
  multiset<long long> values;
  for(int i = 0; i < n; ++i) {
    int t; cin >> t;
    for(int j = 0; j < t; ++j) {
      int x; cin >> x;
      values.insert(x);
    }
  }
  long long result = 0;
  for(int i = 0; i < k; ++i) {
    result += *values.begin();
    values.erase(values.begin());
  }
  cout << result;
}
