#include<bits/stdc++.h>
using namespace std;

// DATA TYPES
typedef long long ll;
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
//

/*
 * Complexity: O(min(E^2 * V * logV, E * logV * Flow))
 */
#define MCMF MincostMaxflow
#define flow_t ll
#define cost_t ll
const flow_t foo = (flow_t) 1e18;
const cost_t coo = (cost_t) 1e18;
namespace MincostMaxflow {
  const int maxv = 1e5 + 5;
  const int maxe = 1e6 + 5;
  int n, s, t, E;
  int adj[maxe], nxt[maxe], lst[maxv], frm[maxv];
  flow_t cap[maxe], flw[maxe], totalFlow;
  cost_t cst[maxe], pot[maxe], dst[maxv], totalCost;

  void init(int nn, int ss, int tt) {
    n = nn, s = ss, t = tt;
    fill_n(lst, n, -1), E = 0;
  }
  void add(int u, int v, flow_t ca, cost_t co) {
    adj[E] = v, cap[E] = ca, flw[E] = 0, cst[E] = +co, nxt[E] = lst[u], lst[u] = E++;
    adj[E] = u, cap[E] =  0, flw[E] = 0, cst[E] = -co, nxt[E] = lst[v], lst[v] = E++;
  }
  void bellman() {
    fill_n(pot, n, 0);
    while (1) {
      int found = 0;
      for (int u = 0; u < n; u++) for (int e = lst[u]; e != -1; e = nxt[e]) if (flw[e] < cap[e]) {
        int v = adj[e];
        if (pot[v] > pot[u] + cst[e]) {
          pot[v] = pot[u] + cst[e];
          found = 1;
        }
      }
      if (!found) break;
    }
  }
  int dijkstra() {
    priority_queue<pair<cost_t, int> > que;
    fill_n(dst, n, coo), dst[s] = 0;
    que.push(make_pair(-dst[s], s));
    while (que.size()) {
      cost_t dnow = -que.top().first;
      int u = que.top().second;
      que.pop();
      if (dst[u] < dnow) continue;
      for (int e = lst[u]; e != -1; e = nxt[e]) if (flw[e] < cap[e]) {
        int v = adj[e];
        cost_t dnxt = dnow + cst[e] + pot[u] - pot[v];
        if (dst[v] > dnxt) {
          dst[v] = dnxt;
          frm[v] = e;
          que.push(make_pair(-dnxt, v));
        }
      }
    }
    return dst[t] < coo;
  }
  cost_t mincost(int k) {
    totalCost = 0, totalFlow = 0;
    bellman();
    while (totalFlow < k) {
      if (!dijkstra()) break;
      flow_t mn = foo;
      for (int v = t, e = frm[v]; v != s; v = adj[e ^ 1], e = frm[v]) {
        //debug2(adj[e ^ 1], v);
        //debug3(cap[e], flw[e], cap[e] - flw[e]);
        mn = min(mn, cap[e] - flw[e]);
      }
      for (int v = t, e = frm[v]; v != s; v = adj[e ^ 1], e = frm[v]) {
        //debug2(adj[e ^ 1], v);
        flw[e] += mn;
        flw[e ^ 1] -= mn;
      }
      totalFlow += mn;
      //debug2(mn, totalFlow);
      //debug3(dst[t], pot[s], pot[t]);
      totalCost += mn * (dst[t] - pot[s] + pot[t]);
      //debug2(mn * (dst[t] - pot[s] + pot[t]), totalCost);
      for (int u = 0; u < n; u++) pot[u] += dst[u];
      //debug2(totalFlow, totalCost);
    }
    return totalCost;
  }
}

int moves[4][2] = {
  {1, 0}, {0, 1},
  {-1, 0}, {0, -1}
};
int cost[20][102];

int main() {
  //auto beginProgram = chrono::steady_clock::now();
  int noRows, noCols, noTiles;
  scanf("%d %d %d", &noRows, &noCols, &noTiles);
  int noCells = noRows * noCols;
  int noNodes = noCells + 2;
  int src = 0, tgt = noNodes - 1;
  MCMF::init(noNodes, src, tgt);
  int u, v;
  FOR(r, 0, noRows) FOR(c, 0, noCols) {
    scanf("%d", &cost[r][c]);
  }
  int r2, c2;
  FOR(r, 0, noRows) FOR(c, 0, noCols) {
    u = r * noCols + c + 1;
    if (r % 2 != c % 2) {
      MCMF::add(u, tgt, 1, 0);
      continue;
    }
    MCMF::add(src, u, 1, 0);
    FOR(i, 0, 4) {
      r2 = r + moves[i][0], c2 = c + moves[i][1];
      if (0 <= r2 and r2 < noRows and 0 <= c2 and c2 < noCols) {
        v = r2 * noCols + c2 + 1; 
        MCMF::add(u, v, 1, -(cost[r][c] * cost[r2][c2]));
      }
    }
  }
  cost_t minCost = MCMF::mincost(noTiles);
  printf("%lld\n", -minCost);
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}
