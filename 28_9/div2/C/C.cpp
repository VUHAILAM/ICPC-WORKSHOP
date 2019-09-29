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
const int N = 1e5 + 7;

void init() {
  //freopen("??.in", "r", stdin);
  //freopen("??.out", "w", stdout);

}

struct Vertex {
    Vertex *l, *r;
    int sum;

    Vertex(int val) : l(nullptr), r(nullptr), sum(val) {}
    Vertex(Vertex *l, Vertex *r) : l(l), r(r), sum(0) {
        // if (l) sum += l->sum;
        // if (r) sum += r->sum;
    }
};

Vertex* build(int a[], int tl, int tr) {
    if (tl == tr)
        return new Vertex(a[tl]);
    int tm = (tl + tr) / 2;
    return new Vertex(build(a, tl, tm), build(a, tm+1, tr));
}

int get_sum(Vertex* v, int tl, int tr, int l, int r) {
    if (l > r)
        return 0;
    if (l == tl && tr == r)
        return v->sum;
    int tm = (tl + tr) / 2;
    return get_sum(v->l, tl, tm, l, min(r, tm))
         + get_sum(v->r, tm+1, tr, max(l, tm+1), r);
}

Vertex* update(Vertex* v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        return new Vertex(new_val);
    int tm = (tl + tr) / 2;
    if (pos <= tm)
        return new Vertex(update(v->l, tl, tm, pos, new_val), v->r);
    else
        return new Vertex(v->l, update(v->r, tm+1, tr, pos, new_val));
}

Vertex *roots[N];
char op[N];

void solve() {
    int n;
    scanf("%d", &n);
    int a[n + 1];
    FORE(i, 1, n) {
        scanf("%d", &a[i]);
    }
    roots[1] = build(a, 1, n);
    int m;
    scanf("%d", &m);
    int i, j, x, idx = 2;
    while (m--) {
        scanf("%s %d %d", op, &i, &j);
        if (op[0] == 'c') {
            scanf("%d", &x);
            roots[idx++] = update(roots[i], 1, n, j, x);
        } else {
            printf("%d\n", get_sum(roots[i], 1, n, j, j));
        }
    }

  // read the question correctly (is y a vowel?)
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie();
  //auto beginProgram = chrono::steady_clock::now();
  //int t; scanf("%d", &t); while (t--) 
  {
    init();
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}