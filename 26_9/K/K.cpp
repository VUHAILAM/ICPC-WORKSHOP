#include <bits/stdc++.h>
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

// // BIT
// #define bitcount(n) __builtin_popcountll(n)
// //

// // DEBUG
// #define format(x) << #x << ": " << (x)
// #define com << ", "
// #define ndl << "\n"
// #define debug1(x) cerr format(x) ndl;
// #define debug2(x, y) cerr format(x) com format(y) ndl;
// #define debug3(x, y, z) cerr format(x) com format(y) com format(z) ndl;
// void debug_out()
// {
//     cerr << "\n";
// }
// template <typename H, typename... T>
// void debug_out(H h, T... t)
// {
//     cerr << " " << (h);
//     debug_out(t...);
// }
// #define DEBUG(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
// //

// // CONSTANTS
// const long long INF64 = 1e18;
// const int INF32 = 1e9;
// const int MOD = 1e9 + 7;
// const double PI = acos(-1.0L);
// const double EPS = static_cast<double>(1e-9);
// //

// // NUMERICAL OPERATIONS
// #define chmin(a, b) a = min(a, b)
// #define chmax(a, b) a = max(a, b)

// int norm(int a)
// {
//     return ((a % MOD) + MOD) % MOD;
// }

// int mul(int a, int b)
// {
//     return int(a * 1LL * b % MOD);
// }

// int binPow(int a, int k)
// {
//     int ans = 1;
//     for (; k > 0; k >>= 1)
//     {
//         if (k & 1)
//         {
//             ans = mul(ans, a);
//         }
//         a = mul(a, a);
//     }
//     return ans;
// }

// // If I need to find (x / a) % MOD, I need to use this function:
// //    (x / a) % MOD = (x * inv(a)) % MOD
// int inv(int a)
// {
//     int b = binPow(a, MOD - 2);
//     assert(mul(a, b) == 1);
//     return b;
// }
// //

// Init variables here
const int N = 1e5 + 7;

// bool notPrime[N];

// void sieve()
// {
//     FOR(i, 2, N)
//     {
//         if (!notPrime[i])
//         {
//             for (int j = i + i; j < N; j += i)
//             {
//                 notPrime[j] = true;
//             }
//         }
//     }
// }
//int p;
// pair<int, ii> f(int p, int x)
// {
//     for (int a = 0; a < 1000; a++)
//     {
//         for (int b = a; b < 1000; b++)
//         {
//             if ((a * a + b * b) % p == x) {
//                 // debug2(a, b);
//                 return mp(a, ii(b, x));
//             }
//         }
//     }
//     return mp(-1, ii(-1, -1));
// }

// void test()
// {
//     int maxA;
//     for (int p = 2; p <= 3000; p++)
//     {
//         // int p = 1499;
//         maxA = INT_MIN;
//         // debug2(p, notPrime[p]);
//         pair<int, ii> cur;
//         vec<ii> best;
//         if (!notPrime[p])
//         {
            
//             for (int x = 0; x < p; x++)
//             {
//                 // debug3(p, x, f(p, x));
//                 cur = f(p, x);
//                 if (maxA < cur.F) {
//                     maxA = cur.F;
//                     best.clear();
//                     best.pb(cur.S);
//                 } else if (maxA == cur.F) {
//                     best.pb(cur.S);
//                 }
//             }
//             debug3(p, maxA, log2(p));
//             cerr << "b: ";
//             for (ii ppp : best) cerr << ppp.F << "-" << ppp.S << "; ";
//             cerr << "\n";
//         }
        
//     }
// }

bool done[N];

void solve()
{
    // sieve();
    // test();
    int p;
    scanf("%d", &p);
    int x;
    int ans;
    FOR(a, 0, 317) FOR(b, a, 100000) {
        x = ((ll)a * a + (ll)b * b) % p;
        if (!done[x]) {
            done[x] = true;
            ans = a;
        }
    }
    printf("%d\n", ans);
    // read the question correctly (is y a vowel?)
    // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}
/*int f(int x) {
    for(int i = 0; i*i <= x; i++) {
        int t = sqrt(x-i*i);
        if(t*t == (x-i*i)) {
            return min(i,t);
        }
        
    }
    return -1;
}*/
int main()
{
    // ios_base::sync_with_stdio(false); cin.tie();
    //auto beginProgram = chrono::steady_clock::now();
    //int t; scanf("%d", &t); while (t--)
    {
        solve();
    }
    //auto endProgram = chrono::steady_clock::now();
    /*cin >> p;
    int ans = -1;
    int c = 0;
    for(int i = 0; i < p; i++) {
        int fg = f(i);
        if(fg >= ans) {
            ans = fg;
            c = i;
        }
    }
    cout << ans << " " << c;*/
    return 0;
}
