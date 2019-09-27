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

// Init variables here
const int MAXN = 107;

struct Edge
{
    int from, to, capacity, cost;
};

vector<int> adj[MAXN];
int cost[MAXN][MAXN], capacity[MAXN][MAXN];

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<int> m(n, 2);
    deque<int> q;
    q.push_back(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        m[u] = 0;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (m[v] == 2) {
                    m[v] = 1;
                    q.push_back(v);
                } else if (m[v] == 0) {
                    m[v] = 1;
                    q.push_front(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, int s, int t) {
    // adj.assign(N, vector<int>());
    // cost.assign(N, vector<int>(N, 0));
    // capacity.assign(N, vector<int>(N, 0));
    // for (Edge e : edges) {
    //     adj[e.from].push_back(e.to);
    //     adj[e.to].push_back(e.from);
    //     cost[e.from][e.to] = e.cost;
    //     cost[e.to][e.from] = -e.cost;
    //     capacity[e.from][e.to] = e.capacity;
    // }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    // while (flow < K) {
    while (true) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        // int f = K - flow;
        int f = INT_MAX;
        int cur = t;
        while (cur != s) {
            debug3(p[cur] + 1, cur + 1, capacity[p[cur]][cur]);
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    // if (flow < K)
    //     return -1;
    // else
        return cost;
}

void solve() {
  int n, m;
  scanf("%d %d", &n, &m);
  int profit[n];
  profit[0] = 0;
  FOR(u, 1, n) {
      scanf("%d", &profit[u]);
  }
  int u, v, c, p;
  FOR(i, 0, m) {
      scanf("%d %d %d %d", &u, &v, &c, &p);
      u--, v--;
      adj[u].pb(v);
      capacity[u][v] += c;
      cost[u][v] += p;
  }
  FOR(u, 0, n) {
      capacity[u][n] = INF;
      cost[u][n] = -profit[u];
      adj[u].pb(n);
  }
  n++;
  debug1(n);
  printf("%d\n", min_cost_flow(n, 0, n - 1));
  // read the question correctly (is y a vowel?)
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie();
  //auto beginProgram = chrono::steady_clock::now();
  {
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}
  