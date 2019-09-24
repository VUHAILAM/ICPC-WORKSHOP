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
const ll N = 1LL << 32;
ll x, y;

void init() {
  //freopen("??.in", "r", stdin);
  //freopen("??.out", "w", stdout);
    cin >> x >> y;
}
string X;
string Y;
void solve() {
    if (y == 0) {
        cout << "Yes\n";
        return;
    }
    while (y % 2 == 0) y /= 2;
    X = "";
    while (x) {
        X += (char)(x % 2 + '0');
        x /= 2;
    }
    Y = "";
    while (y) {
        Y += (char)(y % 2 + '0');
        y /= 2;
    }
    // debug2(X, Y);
    cout << (X.find(Y) != string::npos ? "Yes\n" : "No\n");
  // read the question correctly (is y a vowel?)
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie();
  //auto beginProgram = chrono::steady_clock::now();
  int t; 
//   scanf("%d", &t); 
  cin >> t;
  while (t--) 
  {
    init();
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}
