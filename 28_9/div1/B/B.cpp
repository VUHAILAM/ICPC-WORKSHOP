#include <bits/stdc++.h>

using namespace std;

const int N = 100010;
const long long M = 1e9 + 5;

int n;
int isShop[N];
pair < int, int > f[N];
vector < pair < int, int > > g[N];

/// centroid stuff


namespace getNearest{
  int child[N];
  int worked[N];

  void predfs(int v, int p) {
    child[v] = 1;
    for(auto [s, w] : g[v]) if(s != p && !worked[s]) {
      predfs(s, v);
      child[v] += child[s];
    }
  }

  int centroid(int v, int p, int r) {
    for(auto [s, w] : g[v]) if(s != p && !worked[s]){
      if(child[s] * 2 >= child[r]) return centroid(s, v, r);
    }
    return v;
  }

  pair < int, int > best;

  void add(int v, int p, int len) {
    if(isShop[v]) best = min(best, make_pair(len, v));
    for(auto [s, w] : g[v]) if(s != p && !worked[s]) {
      add(s, v, len + w);
    }
  }

  void calc(int v, int p, int len) {
    f[v] = min(f[v], make_pair(len + best.first, best.second));
    for(auto [s, w] : g[v]) if(s != p && !worked[s]) {
      calc(s, v, len + w);
    }
  }

  void work(int v){
    predfs(v, -1);

    v = centroid(v, -1, v);
    worked[v] = 1;

    if(isShop[v]) best = make_pair(0, v);
    else best = make_pair((int)M, (int)M);

    for(auto [s, w] : g[v]) if(!worked[s]) {
      calc(s, v, w);
      add(s, v, w);
    }

    if(isShop[v]) best = make_pair(0, v);
    else best = make_pair((int)M, (int)M);

    reverse(g[v].begin(), g[v].end());
    for(auto [s, w] : g[v]) if(!worked[s]) {
      calc(s, v, w);
      add(s, v, w);
    }

    f[v] = min(best, f[v]);
    for(auto [s, w] : g[v]) if(!worked[s]) work(s);
  }

  void progress() {
    for(int i = 0; i <= n; ++i) {
      worked[i] = 0;
    }
    work(1);
  }
};

int tot[N];
long long value[N];

namespace getAnswer{
  int sz;
  long long vals[N];

  int bit[N];
  int child[N];
  int worked[N];

  void predfs(int v, int p) {
    child[v] = 1;
    for(auto [s, w] : g[v]) if(s != p && !worked[s]) {
      predfs(s, v);
      child[v] += child[s];
    }
  }

  int centroid(int v, int p, int r) {
    for(auto [s, w] : g[v]) if(s != p && !worked[s]){
      if(child[s] * 2 >= child[r]) return centroid(s, v, r);
    }
    return v;
  }

  void preadd(int v, int p, int len) {
    vals[sz++] = 1LL * (f[v].first - len) * M + f[v].second;
    for(auto [s, w] : g[v]) if(s != p && !worked[s]) {
      preadd(s, v, len + w);
    }
  }

  void add(int v, int p, int len, int sign) {
    long long t = (f[v].first - len) * 1LL * M + f[v].second;
    int pos = upper_bound(vals, vals + sz, t) - vals;
    for(; pos > 0; pos -= pos & -pos) bit[pos] += sign;
    for(auto [s, w] : g[v]) if(s != p && !worked[s]) {
      add(s, v, len + w, sign);
    }
  }

  void calc(int v, int p, int len) {
    long long t = 1LL * len * M + v;
    int pos = upper_bound(vals, vals + sz, t) - vals + 1;
    for(; pos < N; pos += pos & -pos) tot[v] += bit[pos];
    for(auto [s, w] : g[v]) if(s != p && !worked[s]) {
      calc(s, v, len + w);
    }
  }

  void work(int v){
    predfs(v, -1);

    v = centroid(v, -1, v);
    worked[v] = 1;


    sz = 0;
    vals[sz++] = 1LL * f[v].first * M + f[v].second;;
    for(auto [s, w] : g[v]) if(!worked[s]) {
      preadd(s, v, w);
    }

    sort(vals, vals + sz);
    sz = unique(vals, vals + sz) - vals;

    for(auto [s, w] : g[v]) if(!worked[s]) {
      calc(s, v, w);
      add(s, v, w, 1);
    }

    for(auto [s, w] : g[v]) if(!worked[s]) {
      add(s, v, w, -1);
    }


    long long t = 1LL * f[v].first * M + f[v].second;
    int pos = upper_bound(vals, vals + sz, t) - vals;
    for(; pos > 0; pos -= pos & -pos) bit[pos]++;


    reverse(g[v].begin(), g[v].end());

    for(auto [s, w] : g[v]) if(!worked[s]) {
      calc(s, v, w);
      add(s, v, w, 1);
    }
    pos = upper_bound(vals, vals + sz, v) - vals + 1;
    for(; pos < N; pos += pos & -pos) tot[v] += bit[pos];


    for(auto [s, w] : g[v]) if(!worked[s]) {
      add(s, v, w, -1);
    }

    pos = upper_bound(vals, vals + sz, t) - vals;
    for(; pos > 0; pos -= pos & -pos) bit[pos]--;

    for(auto [s, w] : g[v]) if(!worked[s]) work(s);
  }

  void progress() {
    for(int i = 0; i <= n; ++i) {
      worked[i] = 0;
    }
    work(1);
  }
};

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  while(cin >> n) {
    for(int i = 1; i < n; ++i) {
      int u, v, w;
      cin >> u >> v >> w;
      g[u].emplace_back(v, w);
      g[v].emplace_back(u, w);
    }
    for(int i = 1; i <= n; ++i) {
      cin >> isShop[i];
      f[i] = make_pair((int)M, (int)M);
    }

    getNearest::progress();
    getAnswer::progress();

    int risan = 0;

    for(int i = 1; i <= n; ++i) {
      if(!isShop[i]) risan = max(risan, tot[i]);
    }

    for(int i = 1; i <= n; ++i) {
      tot[i] = 0;
      g[i].clear();
    }

    cout << risan << endl;
  }

  return 0;
}
