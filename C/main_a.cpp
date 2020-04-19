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

struct Array { 
    vector<int> v;
    int pt;

    Array() {
      pt = 0;
    }

    bool operator<(const Array& rhs) const {
      return peek() > rhs.peek();
    }

    void push(int val) {
      v.push_back(val);
      pt++;
    }

    int peek() const {
      return pt > 0 ? v[pt - 1]: -1; 
    }
    int pop() {
      return v[pt--];
    }
};

int main() {
  int n, k; cin >> n >> k;
  multiset<Array> st;
  long long all = 0;
  int was = 0;
  for(int i = 0; i < n; ++i) {
    int m; cin >> m;
    was += m;
    Array cur;
    for(int j = 0; j < m; ++j) {
      int x; cin >> x;
      all += x;
      cur.push(x);
    }
    st.insert(cur);
  }
  
  while(was != k) {
    auto min = *st.begin();
    int best = min.peek();
    st.erase(st.find(min));
    if(best < 0) {
      continue;
    }
    --was;
    all -= best;
    min.pop();
    st.insert(min);
  }
  cout << all << endl;
}
