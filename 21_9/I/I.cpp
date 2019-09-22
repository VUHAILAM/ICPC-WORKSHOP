#include <bits/stdc++.h>
using namespace std;

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
std::pair<T, U> operator+(const std::pair<T, U> &L, const std::pair<T, U> &R)
{
  return {L.first + R.first, L.second + R.second};
}
//

// LOOP
#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define FORE(i, a, b) for (int i = (a); i <= (b); i++)
#define FORD(i, a, b) for (int i = (a); i >= (b); i--)
//

// DEBUG
#define format(x) << #x << ": " << (x)
#define com << ", "
#define ndl << "\n"
#define debug1(x) cerr format(x) ndl;
#define debug2(x, y) cerr format(x) com format(y) ndl;
#define debug3(x, y, z) cerr format(x) com format(y) com format(z) ndl;
void debug_out()
{
  cerr << "\n";
}
template <typename H, typename... T>
void debug_out(H h, T... t)
{
  cerr << " " << (h);
  debug_out(t...);
}
#define DEBUG(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
//

// Init variables here
const int N = 2e6 + 7;
int n;
vec<int> adj[N];

void init()
{
  //freopen("??.in", "r", stdin);
  //freopen("??.out", "w", stdout);
  scanf("%d", &n);
  int j;
  FORE(i, 2, n)
  {
    scanf("%d", &j);
    adj[i].pb(j);
    adj[j].pb(i);
  }
}

bool in[N];
bool out[N];
int cnt[N];

void dfsIn(int u, int p)
{
  in[u] = true;
  for (int v : adj[u])
  {
    if (v == p)
      continue;
    dfsIn(v, u);
    if (in[v])
    {
      in[u] = false;
      cnt[u]++;
    }
  }
}

void dfsOut(int u, int p)
{
  if (p != -1 and cnt[p] - (in[u] ? 1 : 0) == 0)
    cnt[u]++;
  for (int v : adj[u])
  {
    if (v == p)
      continue;
    out[v] = in[v];
    if (cnt[u] - (in[v] ? 1 : 0) == 0)
      out[v] = false;
    dfsOut(v, u);
  }
}

void solve()
{
  dfsIn(1, -1);
  out[1] = in[1];
  dfsOut(1, -1);
  FORE(u, 1, n)
  {
    // debug3(u, in[u], out[u]);
    if (out[u])
      printf("%d\n", u);
  }
  // read the question correctly (is y a vowel?)
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main()
{
  //auto beginProgram = chrono::steady_clock::now();
  {
    init();
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}
