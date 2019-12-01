#include <bits/stdc++.h>

using namespace std;

const int N = 110;

int n;
int lab[N];
int a[N][N];
int b[N][N];

int find(int x) {
  return lab[x] < 0 ? x : lab[x] = find(lab[x]);
}

bool join(int x, int y) {
  x = find(x); y = find(y);
  if(x == y) return false;
  lab[x] += lab[y];
  lab[y] = x;
  return true;
}

int dfs(int v, int pr, int to, int flow) {
  if(v == to) return flow;
  for(int s = 1; s <= n; ++s) if(s != pr && a[v][s] != -1) {
    int x = dfs(s, v, to, min(flow, a[v][s]));
    if(x != -1) return x;
  }
  return -1;
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  vector < pair < int, pair < int, int > > > edges;

  cin >> n;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      cin >> a[i][j];
      b[i][j] = a[i][j];
      if(a[i][j] != -1) edges.emplace_back(a[i][j], make_pair(i, j));
    }
  }

  memset(a, -1, sizeof a);
  sort(edges.rbegin(), edges.rend());
  memset(lab, -1, sizeof lab);

  for(auto p : edges) {
    if(join(p.second.first, p.second.second)) {
      a[p.second.first][p.second.second] = p.first;
      a[p.second.second][p.second.first] = p.first;
    }
  }

  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) if(i != j){
      if(dfs(i, -1, j, (int)1e9) != b[i][j]) {
        cout << "NO" << endl;
        return 0;
      }
    }
  }

  cout << "YES" << endl;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      if(i != j) a[i][j] = max(a[i][j], 0);
      cout << a[i][j] << " ";
    }
    cout << endl;
  }

  return 0;
}