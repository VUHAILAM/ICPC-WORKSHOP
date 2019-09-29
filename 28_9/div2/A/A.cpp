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

int norm(int a)
{
    return ((a % MOD) + MOD) % MOD;
}

int mul(int a, int b)
{
    return int(a * 1LL * b % MOD);
}

int binPow(int a, int k)
{
    int ans = 1;
    for (; k > 0; k >>= 1)
    {
        if (k & 1)
        {
            ans = mul(ans, a);
        }
        a = mul(a, a);
    }
    return ans;
}

// If I need to find (x / a) % MOD, I need to use this function:
//    (x / a) % MOD = (x * inv(a)) % MOD
int inv(int a)
{
    int b = binPow(a, MOD - 2);
    assert(mul(a, b) == 1);
    return b;
}
//

// Init variables here
const int N = 1e6 + 7;

void init()
{
    //freopen("??.in", "r", stdin);
    //freopen("??.out", "w", stdout);
}

// ll mass[N];
// int top[N];
// int pre[N];

// void solve() {
//   int n;
//   scanf("%d", &n);
//   int t, m;
//   ll res = 0;
//   FORE(i, 1, n) {
//       scanf("%d %d", &t, &m);
//       pre[i] = t;
//       if (m) {
//           top[i] = m;
//           mass[i] = mass[t] + m;
//       } else {
//           top[i] = top[pre[t]];
//           mass[i] = mass[pre[t]];
//       }
//       res += mass[i];
//   }
//   printf("%lld\n", res);
//   // read the question correctly (is y a vowel?)
//   // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
// }
struct Node
{
    ll top;
    ll sum;
    Node *next;
    Node(ll _top, Node *_next)
    {
        next = _next;
        if (_top)
        {
            top = _top;
            sum = getSum(next) + top;
        }
        else
        {
            top = getTop(next->next);
            sum = getSum(next->next);
        }
    }
    static ll getSum(Node *s)
    {
        return (s ? s->sum : 0);
    }

    ll getTop(Node *s)
    {
        return (s ? s->top : 0);
    }
};

Node *push(Node *s, ll v)
{
    Node *ns = new Node(v, s);
    return ns;
}

pair<Node *, ll> pop(Node *s)
{
    return mp(s->next, s->top);
}

void solve()
{
    int n;
    scanf("%d", &n);
    int t;
    ll m;
    ll res = 0;
    vector<Node *> nodes(n + 1, NULL);
    FORE(i, 1, n)
    {
        scanf("%d %lld", &t, &m);
        if (m) {
            nodes[i] = push(nodes[t], m);
        } else {
            nodes[i] = pop(nodes[t]).first;
        }
        res += Node::getSum(nodes[i]);
        // debug1(res);
    }
    // debug1(res);
    printf("%lld\n", res);
}

int main()
{
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