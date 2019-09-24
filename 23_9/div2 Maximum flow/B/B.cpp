#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

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

#define vec vector
#define pb push_back

// Init variables here
const int N = 107;
int n;
int src;
int tgt;
vec<int> adj[N];
ll capacity[N][N];
ll flow[N][N];
int idx[N][N];
int pre[N];

void init() {
  //freopen("??.in", "r", stdin);
  //freopen("??.out", "w", stdout);
  int m;
  scanf("%d %d", &n, &m);
  src = 1, tgt = n;
  //FORE(i, 1, n) FORE(j, 1, n) capacity[i][j] = -1;
  int u, v;
  ll c;
  FORE(i, 1, m) {
    scanf("%d %d %lld", &u, &v, &c);
    adj[u].pb(v), adj[v].pb(u);
    capacity[u][v] = capacity[v][u] = c;
    idx[u][v] = idx[v][u] = i;
  }
}

bool dfs(int u, int p) {
  pre[u] = p;
  if (u == tgt) return true;
  for (int v : adj[u]) {
    if (pre[v]) continue;
    if (capacity[u][v] - flow[u][v] != 0) {
      if (dfs(v, u)) return true;
    }
  }
  return false;
}

bool foundAugmentPath() {
  FORE(u, 1, n) pre[u] = 0;
  return dfs(src, -1);
}

void increaseFlow() {
  ll minResidual = LLONG_MAX;
  int u = tgt, p;
  while (u != src) {
    p = pre[u];
    chmin(minResidual, capacity[p][u] - flow[p][u]);
    u = p;
  }
  u = tgt;
  while (u != src) {
    p = pre[u];
    flow[p][u] += minResidual;
    flow[u][p] -= minResidual;
    u = p;
  }
}

ll maxFlow() {
  while (foundAugmentPath()) {
    increaseFlow();
  }
  ll totalFlow = 0;
  for (int u : adj[src]) totalFlow += flow[src][u];
  return totalFlow;
}

vector<int> cut;

void dfs2(int u, int p) {
  pre[u] = p;
  /*
  if (p != -1
    and capacity[p][u] > 0
    and capacity[p][u] == flow[p][u]) {
    cut.push_back(idx[p][u]);
    return;
  }
  for (int v : adj[u]) {
    debug3(p, u, v);
    debug3(pre[v], capacity[u][v], flow[u][v]);
    if (pre[v]) continue;
    dfs2(v, u);
  }
  */
  FORE(v, 1, n) {
    if (pre[v] or capacity[u][v] == flow[u][v]) continue;
    dfs2(v, u);
  }
}

void findCut() {
  FORE(u, 1, n) pre[u] = 0;
  dfs2(src, -1);
   
  FORE(u, 1, n) FORE(v, 1, n) {
    if (pre[u] and !pre[v] and capacity[u][v]) {
      cut.push_back(idx[u][v]);
    }
  }
 
  sort(cut.begin(), cut.end());
}

void solve() {
  ll maxF = maxFlow();
  findCut();
  printf("%d %lld\n", (int)cut.size(), maxF);
  for (int i : cut) printf("%d ", i);
  printf("\n");
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  //auto beginProgram = chrono::steady_clock::now();
  {
    init();
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}