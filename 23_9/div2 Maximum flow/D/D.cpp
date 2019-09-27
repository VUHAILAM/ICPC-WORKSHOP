#include<bits/stdc++.h>
using namespace std;

// DATA TYPES
typedef long long ll;
//

// CONTAINERS
#define vec vector
#define pb push_back
//

// LOOP
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define FORE(i, a, b) for(int i = (a); i <= (b); i++)
#define FORD(i, a, b) for(int i = (a); i >= (b); i--)
//

// DEBUG
#define format(x) << #x << ": " << (x)
#define com << ", "
#define ndl << "\n"
#define debug1(x) cerr format(x) ndl;
#define debug2(x, y) cerr format(x) com format(y) ndl;
#define debug3(x, y, z) cerr format(x) com format(y) com format(z) ndl;
void debug_out() { cerr << "\n"; }
template <typename H, typename... T> 
void debug_out(H h, T... t) { cerr << " " << (h); debug_out(t...); }
#define DEBUG(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
// 

// NUMERICAL OPERATIONS
#define chmin(a, b) a = min(a, b)
#define chmax(a, b) a = max(a, b)

struct FlowEdge {
  int v, u, idx;
  long long cap, flow = 0;
  FlowEdge(int v, int u, int idx, long long cap) : v(v), u(u), idx(idx), cap(cap){}
};

vec<ll> flows;
vec<stack<int> > paths;

struct Dinic {
  const long long flow_inf = 1e18;
  vector<FlowEdge> edges;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;
  vec<vec<int> > adjE;
  vec<int> preE;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adjE.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, int idx, long long cap) {
    edges.emplace_back(v, u, idx, cap);
    edges.emplace_back(u, v, idx, 0);
    adjE[v].pb(m);
    adjE[u].pb(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adjE[v]) {
        if (edges[id].cap - edges[id].flow < 1)
          continue;
        if (level[edges[id].u] != -1)
          continue;
        level[edges[id].u] = level[v] + 1;
        q.push(edges[id].u);
      }
    }
    return level[t] != -1;
  }

  long long dfs(int v, long long pushed) {
    if (pushed == 0)
      return 0;
    if (v == t)
      return pushed;
    for (int& cid = ptr[v]; cid < (int)adjE[v].size(); cid++) {
      int id = adjE[v][cid];
      int u = edges[id].u;
      //assert(edges[id].cap <= 1);
      //assert(edges[id].cap - edges[id].flow <= 1);
      if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
        continue;
      long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
      if (tr == 0)
        continue;
      edges[id].flow += tr;
      edges[id ^ 1].flow -= tr;
      return tr;
    }
    return 0;
  }

  int lastE;

  bool dfs2(int u, int j) {
    if (u == t) {
      lastE = j;
      return true;
    }
    //debug1(u);
    for (int i : adjE[u]) {
      //debug2(i, preE[i]);
      //debug3(edges[i].v, edges[i].u, edges[i].flow);
      if (preE[i] != -1 or edges[i].flow <= 0LL)
        continue;
      preE[i] = j; 
      if (dfs2(edges[i].u, i))
        return true;
    }
    return false;
  }

  bool foundPath() {
    FOR(i, 0, m) preE[i] = -1;
    return dfs2(s, -1);
  }

  ll decreaseFlow(stack<int> &path) {
    ll minF = LLONG_MAX;
    int i = lastE;
    while (i != -1) {
      chmin(minF, edges[i].flow);
      //path.push(edges[i].idx);
      path.push(i);
      i = preE[i];
    }
    i = lastE;
    while (i != -1) {
      edges[i].flow -= minF;
      i = preE[i];
    }
    return minF;
  }

  long long flow() {
    preE.resize(m);
    long long f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, flow_inf)) {
        //debug1(pushed);
        //assert(pushed == 1);
        f += pushed;
        debug1(f);
        if (f >= 2LL) break;
      }
      if (f >= 2LL) break;
    }
    assert(f <= 2LL);
    if (f == 2LL) {
    ll curF;
    FOR(i, 0, 2) {
      foundPath();
      stack<int> path;
      curF = decreaseFlow(path);
      //debug1(curF);
      if (curF <= 0LL) break;
      flows.pb(curF);
      paths.pb(path);
      //debug1(paths.size());
    }
    }
    return f;
  }
};

void solve() {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);
  if (s == t) {
    printf("YES\n");
    printf("%d\n", t);
    printf("%d\n", t);
    return;
  }
  Dinic dinic(n, --s, --t);
  int u, v;
  FOR(i, 0, m) {
    scanf("%d %d", &u, &v);
    if (u == v) continue;
    dinic.add_edge(--u, --v, i, 1);
  }
  ll maxFlow = dinic.flow();
  //debug1(maxFlow);
  if (maxFlow != 2) {
    printf("NO\n");
    return;
  }
  printf("YES\n");
  int noPaths = paths.size();
  //printf("%d\n", noPaths);
  vec<FlowEdge> &edges = dinic.edges;
  FOR(i, 0, noPaths) {
    stack<int> &path = paths[i];
    //printf("%lld %d", flows[i], (int)path.size());
    printf("%d", s + 1);
    while (path.size()) {
      printf(" %d", edges[path.top()].u + 1);
      path.pop();
    }
    printf("\n");
  }
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  //auto beginProgram = chrono::steady_clock::now();
  {
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}


