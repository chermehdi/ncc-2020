//
// Author Maxheap
//
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  int cnt = 1;
  while (n--) {
    int m;
    string s;
    cin >> m >> s;
    s.erase(s.begin() + m - 1, s.begin() + m);
    cout << cnt++ << ' ' << s << '\n';
  }
}
