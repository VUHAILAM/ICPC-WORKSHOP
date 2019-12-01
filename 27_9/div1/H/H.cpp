#include <bits/stdc++.h>

using namespace std;

const int N = 100010;

int n;
int cnt[N];
long long ans;
long long f[N];
vector < int > g[N];

void dfs(int v, int p) {
  cnt[v] = 1;
  for(int s : g[v]) if(s != p){
    dfs(s, v);
    ans -= 1LL * cnt[s] * f[v];
    ans -= 1LL * f[s] * cnt[v];
    cnt[v] += cnt[s];
    f[v] += cnt[s] + f[s];
  }
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n; cin >> n;
  for(int i = 1; i < n; ++i) {
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  ans = 1LL * n * (n - 1) * (n - 2) / 6;

  dfs(1, 0);

  cout << ans << endl;

  return 0;
}