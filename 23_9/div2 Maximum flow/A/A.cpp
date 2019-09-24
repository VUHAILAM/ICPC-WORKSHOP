#include <bits/stdc++.h>
using namespace std;
const int Nmax = 1005;
double c[Nmax][Nmax];
double f[Nmax][Nmax];
int trace[Nmax];
double cap[Nmax][Nmax];
int n, m, s, t;

bool FindPath()
{
    memset(trace, 0, sizeof(trace) / sizeof(trace[0]));
    queue<int> q;
    q.push(s);
    trace[s] = n + 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v = 1; v <= n; v++)
        {
            if (trace[v] == 0 && c[u][v] - f[u][v] != 0)
            {
                trace[v] = u;
                if (v == t)
                {
                    return true;
                }
                q.push(v);
            }
        }
    }
    return false;
}

void increFLow()
{
    int u, v;
    double delta = DBL_MAX;
    v = t;
    while (v != s)
    {
        u = trace[v];
        delta = min(delta, c[u][v] - f[u][v]);
        v = u;
    }
    v = t;
    while (v != s)
    {
        u = trace[v];
        f[u][v] += delta;
        f[v][u] -= delta;
        v = u;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    s = 1, t = n;
    vector<pair<int, int>> edge;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        cin >> cap[u][v];
        c[u][v] += cap[u][v];
        c[v][u] += cap[u][v];
        edge.push_back({u, v});
    }
    while (FindPath())
    {
        increFLow();
    }
    double ans = 0;

    for (int v = 1; v <= n; v++)
    {
        if (f[1][v] > 0)
        {
            ans += f[1][v];
        }
    }

    cout << setprecision(7) << fixed << ans << "\n";
    for (auto i : edge)
    {
        int u = i.first;
        int v = i.second;
        double flo = f[u][v];
        ans = max(flo, -flo);
        ans = min(ans, cap[u][v]);
        //ans = min(cap[u][v], max(flo, -flo));
        if (flo < 0)
            ans = -ans;
        cout << ans << "\n";
        f[u][v] -= ans;
        f[v][u] += ans;
    }
    return 0;
}

/*
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

// Init variables here
const int N = 107;
int n;
int src = 0;
int tgt;
int capacity[N][N];
int flow[N][N];
bool visited[N];
int pre[N];
vec<pair<ii, int> > edges;

void init() {
  //freopen("??.in", "r", stdin);
  //freopen("??.out", "w", stdout);
  int m;
  cin >> n >> m;
  tgt = n - 1;
  int u, v, c;
  while (m--) {
    cin >> u >> v >> c;
    u--, v--;
    capacity[u][v] += c;
    capacity[v][u] += c;
    edges.pb(mp(ii(u, v), c));
  }
}

bool dfs(int u, int p) {
  visited[u] = true;
  pre[u] = p;
  if (u == tgt) return true;
  FOR(v, 0, n) {
      if (visited[v]) continue;
      if (capacity[u][v] - flow[u][v] != 0) {
          if (dfs(v, u)) return true;
      }
  }
  return false;
}

bool foundAugmentPath() {
  FOR(u, 0, n) visited[u] = false;
  return dfs(src, -1);
}

void increaseFlow() {
  int minResidual = INT_MAX;
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

int maxFlow() {
  while (foundAugmentPath()) {
      increaseFlow();
  }
  int totalFlow = 0;
  FOR(u, 0, n) {
      if (flow[src][u] > 0) {
        // debug3(src, u, flow[src][u]);
        totalFlow += flow[src][u];
      }
  }
  return totalFlow;
}

void solve() {
  double maxF = maxFlow();
  cout << setprecision(7) << fixed;
  cout << maxF << "\n";
  ii e;
  double c;
  double f;
  double ans;
  for (auto p : edges) {
    e = p.F;
    c = p.S;
    f = flow[e.F][e.S];
    ans = max(f, -f);
    ans = min(ans, c);
    if (f < 0) ans = -ans;
    cout << ans << "\n";
    flow[e.F][e.S] -= ans;
    flow[e.S][e.F] += ans;
  }
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie();
  //auto beginProgram = chrono::steady_clock::now();
  {
    init();
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}


*/