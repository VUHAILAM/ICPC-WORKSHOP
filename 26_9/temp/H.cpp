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
const int N = 1e6 + 7;
int n;
int a[N];

void init() {
    scanf("%d", &n);
    FORE(i, 1, n) scanf("%d", &a[i]);
  //freopen("??.in", "r", stdin);
  //freopen("??.out", "w", stdout);

}

int b[N];
int MEX;
ll cnt[N];

void solve() {
  FORE(i, 1, n) b[i] = a[i];
  sort(b + 1, b + n + 1);
  MEX = b[n] + 1;
  FORE(i, 1, n) {
      if (b[i] > b[i -1] + 1) {
          MEX = b[i - 1] + 1;
          break;
      }
  }
  if (MEX == 0) {
      printf("%d\n", binPow(2, n - 1));
      return;
  }
  vec<ii> v;
  int R;
  FORE(L, 1, n) {
      if (a[L] < MEX) {
          for (R = L + 1; R <= n; R++) {
              if (a[R] > MEX) {
                  break;
              }
          }
          
        R--;
        v.pb(ii(L, R));
        L = R;
      }
  }
  v[0].F = 1;
  v.back().S = n;
  int sz = v.size();
    FOR(i, 1, sz) {
        cnt[i] = v[i].F - v[i - 1].S;
    }
    FORD(i, sz - 2, 1) {
        (cnt[i] *= cnt[i + 1]) %= MOD;
    }
    ll ans = 0;
    FOR(i, 1, sz) {

    }
  // read the question correctly (is y a vowel?)
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie();
  //auto beginProgram = chrono::steady_clock::now();
  int t; scanf("%d", &t); while (t--) 
  {
    init();
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}
