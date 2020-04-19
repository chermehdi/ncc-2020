//
// @author MaxHeap
//
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <string> 
// BEGIN kratos/datastructures/trie.hpp

namespace kratos {
  using std::vector;
  using std::string;

  class Trie {
    private:
      vector<Trie*> children;
      int node_count;
      bool leaf;

    public:
      int instance_counter = 0;

      Trie(): children(128), node_count(0), leaf(false){
      }

      void insert(string &s) {
        Trie* cur = this;
        for(int i = 0; i < s.length(); ++i) {
          int c = s[i];
          if(cur->children[c] == nullptr) {
            cur->children[c] = new Trie();
            this->instance_counter++;
          }
          cur->node_count++;
          cur = cur->children[c];
        }
        cur->leaf = true;
      }

      int prefix_count(string &s) {
        Trie* cur = this;
        for(int i = 0; i < s.length(); ++i) {
          int c = s[i];
          if(cur->children[c] == nullptr) {
            return 0;
          }
          cur = cur->children[c];
        }
        return cur->node_count;
      }
  };
};
// END kratos/datastructures/trie.hpp
// BEGIN kratos/misc/constants.hpp

using std::vector;

namespace kratos {
  const int INF_INT = 1 << 31;
  const long long INF_LONG = 1LL << 60;
  const vector<int> dx4 = {-1, 1, 0, 0};
  const vector<int> dy4 = {0, 0, -1, 1};
};
// END kratos/misc/constants.hpp

using namespace std;

using kratos::Trie;

vector<string> grid;
vector<vector<bool>> seen;
Trie root;

int n, m, q;

bool is_safe(int x, int y) {
  return x >= 0 && y >= 0 && x < n && y < m;
}

void dfs(int x, int y, string s) {
  seen[x][y] = true;
  root.insert(s);
  for(int i = 0; i < 4; ++i) {
    int xx = x + kratos::dx4[i];
    int yy = y + kratos::dy4[i];
    if(is_safe(xx, yy) && !seen[xx][yy]) {
      dfs(xx, yy, s + grid[xx][yy]);
    }
  }
  s.pop_back();
  seen[x][y] = false;
}

int main() {
  cin >> n >> m >> q;
  grid.resize(n);
  seen.assign(n, vector<bool>(m, false));

  for(int i = 0; i < n; ++i) {
    cin >> grid[i];
  }
  string acc(1, grid[0][0]);
  dfs(0, 0, acc); 

  while(q--) {
    string s; int p;
    cin >> p >> s;
    int count = root.prefix_count(s);
    if(count > p) {
      cout << "Say Whaat?" << '\n';
    }else {
      cout << count << '\n';
    }
  }
}

