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

// Init variables here
const int N = 1e2 + 7;
int n, m;
// char a[N][N];
string a[N];
void init() {
  //freopen("??.in", "r", stdin);
  //freopen("??.out", "w", stdout);
//   scanf("%d %d", &n, &m);
//   FOR(i, 0, n) scanf("%s", a[i]);
    cin >> n >> m;
    FOR(i, 0, n) cin >> a[i];
}

bool ok(int i, int j) {
    return a[i][j] == 'F'
    and (i == 0 or a[i - 1][j] != 'B')
    and (j == 0 or a[i][j - 1] != 'B');
}

// void check() {
//     FOR(i, 0, n) FOR(j, 0, m) {
//         if (bad(i, j)) {
//             cerr << "bad\n";
//             return;
//         }
//     }
// }

void solve() {
  FOR(i, 0, n) FOR(j, 0, m) {
      if (ok(i, j)) {
          //debug2(i, j);
          a[i][j] = 'B';
      }
  }
//   check();
//   FOR(i, 0, n) printf("%s\n", a[i]); 
    FOR(i, 0, n) cout << a[i] << "\n";
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
