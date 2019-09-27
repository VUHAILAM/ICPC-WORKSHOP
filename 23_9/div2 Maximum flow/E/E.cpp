#include<bits/stdc++.h>
using namespace std;

// DATA TYPES
typedef long long ll;
#define double long double
//

// CONTAINERS
#define vec vector
#define pb push_back
#define ALL(x) begin(x), end(x)
#define SZ(x) (int)x.size()
#define mp make_pair
#define ii pair<int, int>
#define F first
#define S second
template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U> &L, const std::pair<T,U> &R) {
  return {L.first + R.first, L.second + R.second};
}
//

// LOOP
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define FORE(i, a, b) for(int i = (a); i <= (b); i++)
#define FORD(i, a, b) for(int i = (a); i >= (b); i--)
//

// BIT
#define bitcount(n) __builtin_popcountll(n)
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

// CONSTANTS
const long long INF64 = 1e18;
const int INF32 = 1e9;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0L);
const double EPS = static_cast<double>(1e-9);
//

// NUMERICAL OPERATIONS
#define chmin(a, b) a = min(a, b)
#define chmax(a, b) a = max(a, b)

int norm(int a) {
  return ((a % MOD) + MOD) % MOD;
}

int mul(int a, int b) {
  return int(a * 1LL * b % MOD);
}

int binPow(int a, int k) {
  int ans = 1;
  for (; k > 0; k >>= 1) {
    if (k & 1) {
      ans = mul(ans, a);
    }
    a = mul(a, a);
  }
  return ans;
}

// If I need to find (x / a) % MOD, I need to use this function:
//    (x / a) % MOD = (x * inv(a)) % MOD
int inv(int a) {
  int b = binPow(a, MOD - 2);
  assert(mul(a, b) == 1);
  return b;
}
//

const long long flow_inf = 1e18;

struct FlowEdge {
  int v, u;
  long long cap, flow = 0;
  FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;
  vec<int> preE;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }

  void add_edge(int v, int u, long long cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
  }

  bool bfs() {
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int id : adj[v]) {
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

  int lastE;

  long long dfs(int v, long long pushed) {
    if (pushed == 0)
      return 0;
    if (v == t)
      return pushed;
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
      int id = adj[v][cid];
      int u = edges[id].u;
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

  bool dfs2(int u, int j) {
    if (u == t) {
      lastE = j;
      return true;
    }
    for (int i : adj[u]) {
      if (preE[i] != -1 or edges[i].flow <= 0) continue;
      preE[i] = j;
      if (dfs2(edges[i].u, i)) return true;
    }
    return false;
  }

  bool foundPath() {
    FOR(i, 0, m) preE[i] = -1;
    return dfs2(s, -2);
  }

  ll decreaseFlow(vec<bool> &take) {
    ll minF = LLONG_MAX;
    int i = lastE;
    while (i != -2) {
      FlowEdge &e = edges[i];
      //debug3(e.v, e.u, e.flow);
      take[e.v] = false;
      chmin(minF, e.flow);
      i = preE[i];
    }
    i = lastE;
    while (i != -2) {
      edges[i].flow -= minF;
      //edges[i ^ 1].flow += minF;
      i = preE[i];
    }
    return minF;
  }

  long long flow(vec<bool> &take) {
    long long f = 0;
    while (true) {
      fill(level.begin(), level.end(), -1);
      level[s] = 0;
      q.push(s);
      if (!bfs())
        break;
      fill(ptr.begin(), ptr.end(), 0);
      while (long long pushed = dfs(s, flow_inf)) {
        f += pushed;
      }
    }
    preE.resize(m);
    ll curF;
    while (foundPath()) {
      curF = decreaseFlow(take);
      if (curF <= 0) break;
    }
    return f;
  }
};

void solve() {
  int n;
  scanf("%d", &n);
  Dinic dinic(n + 2, 0, n + 1);
  int x[n + 1];
  ll sum = 0;
  vec<bool> take(n + 1, true);
  FORE(i, 1, n) {
    scanf("%d", &x[i]);
    if (x[i] > 0) {
      sum += x[i];
      dinic.add_edge(0, i, x[i]);
    } else {
      take[i] = false;
      dinic.add_edge(i, n + 1, -x[i]);
    }
  }
  int k, j;
  vec<int> must[n + 1];
  FORE(i, 1, n) {
    scanf("%d", &k);
    while (k--) {
      scanf("%d", &j);
      must[i].pb(j);
      dinic.add_edge(i, j, flow_inf);
    }
  }
  ll maxF = dinic.flow(take);
  //debug1(maxF);
  /*
  vec<bool> done(n + 1, false);
  ll sum = 0;
  FORE(i, 1, n) {
    if (take[i]) {
      if (!done[i]) {
        done[i] = true;
        sum += x[i];
      }
      vec<int> &v = must[i];
      for (int j : v) {
        if (!done[j]) {
          done[j] = true;
          sum += x[j];
        }
      }
    }
  }
  */
  sum -= maxF;
  printf("%lld\n", sum);
  // read the question correctly (is y a vowel?)
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

