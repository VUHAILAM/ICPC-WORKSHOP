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
#define flow_t int
#define cost_t ll
const flow_t foo = (flow_t) 1e9;
const cost_t coo = (cost_t) 1e18;
const int N = 2005;

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
  int add(int u, int v, flow_t ca, cost_t co) {
    adj[E] = v, cap[E] = ca, flw[E] = 0, cst[E] = +co, nxt[E] = lst[u], lst[u] = E++;
    adj[E] = u, cap[E] =  0, flw[E] = 0, cst[E] = -co, nxt[E] = lst[v], lst[v] = E++;
    return E - 2;
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
  cost_t mincost() {
    totalCost = 0, totalFlow = 0;
    bellman();
    while (1) {
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
    }
    return totalCost;
  }
}

int start[N], duration[N], profit[N];
int e[N];

int main() {
  //auto beginProgram = chrono::steady_clock::now();
  set<int> st;
  int n, k;
  scanf("%d %d", &n, &k);
  FOR(i, 0, n) {
    scanf("%d %d %d", &start[i], &duration[i], &profit[i]);  
    start[i]++;
    st.insert(start[i]);
    st.insert(start[i] + duration[i]);
  }
  map<int, int> id;
  int fin = 1, t;
  while (st.size()) {
    t = *st.begin();
    st.erase(t);
    id[t] = fin++;
  }
  int noNodes = 2 + id.size();
  int src = 0, tgt = noNodes - 1;
  MCMF::init(noNodes, src, tgt);
  MCMF::add(src, 1, k, 0);
  FOR(i, 2, fin) MCMF::add(i - 1, i, foo, 0);
  MCMF::add(fin - 1, tgt, foo, 0);
  int t1, t2;
  FOR(i, 0, n) {
    t1 = id[start[i]];
    t2 = id[start[i] + duration[i]];
    e[i] = MCMF::add(t1, t2, 1, -profit[i]);
  }
  MCMF::mincost();
  FOR(i, 0, n) {
    printf("%d ", (MCMF::flw[e[i]] > 0 ? 1 : 0));
  }
  printf("\n");
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}
