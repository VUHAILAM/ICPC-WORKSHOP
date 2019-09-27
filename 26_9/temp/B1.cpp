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
const int N = 1e3 + 7;
int n;
ll a[N][N];

void init()
{
    //freopen("??.in", "r", stdin);
    //freopen("??.out", "w", stdout);
    cin >> n;
    FOR(i, 0, n)
        FOR(j, 0, n) cin >> a[i][j];
}

const ll INF = INF64;
ll dist[N];
int p[N];
int type[N];
deque<int> q;
ll f[N][N];

vector<int> assignment()
{
    int m = n * 2 + 2;
    int s = m - 2, t = m - 1;
    ll cost = 0;
    while (true)
    {
        FOR(u, 0, m) {
            dist[u] = INF;
            p[u] = 0;
            type[u] = 2;
        }
        dist[s] = 0;
        p[s] = -1;
        type[s] = 1;
        q.push_back(s);
        while (!q.empty())
        {
            int v = q.front();
            q.pop_front();
            type[v] = 0;
            if (v == s)
            {
                for (int i = 0; i < n; ++i)
                {
                    if (f[s][i] == 0)
                    {
                        dist[i] = 0;
                        p[i] = s;
                        type[i] = 1;
                        q.push_back(i);
                    }
                }
            }
            else
            {
                if (v < n)
                {
                    for (int j = n; j < n + n; ++j)
                    {
                        if (f[v][j] < 1 && dist[j] > dist[v] + a[v][j - n])
                        {
                            dist[j] = dist[v] + a[v][j - n];
                            p[j] = v;
                            if (type[j] == 0)
                                q.push_front(j);
                            else if (type[j] == 2)
                                q.push_back(j);
                            type[j] = 1;
                        }
                    }
                }
                else
                {
                    for (int j = 0; j < n; ++j)
                    {
                        if (f[v][j] < 0 && dist[j] > dist[v] - a[j][v - n])
                        {
                            dist[j] = dist[v] - a[j][v - n];
                            p[j] = v;
                            if (type[j] == 0)
                                q.push_front(j);
                            else if (type[j] == 2)
                                q.push_back(j);
                            type[j] = 1;
                        }
                    }
                }
            }
        }

        ll curcost = INF;
        for (int i = n; i < n + n; ++i)
        {
            if (f[i][t] == 0 && dist[i] < curcost)
            {
                curcost = dist[i];
                p[t] = i;
            }
        }
        if (curcost == INF)
            break;
        cost += curcost;
        for (int cur = t; cur != -1; cur = p[cur])
        {
            int prev = p[cur];
            if (prev != -1)
                f[cur][prev] = -(f[prev][cur] = 1);
        }
    }

    vector<int> answer(n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (f[i][j + n] == 1)
                answer[i] = j;
        }
    }
    return answer;
}

void solve()
{
    vec<int> res = assignment();
    int sum = 0;
    FOR(i, 0, n)
    sum += a[i][res[i]];
    cout << sum << "\n";
    FOR(i, 0, n)
    {
        cout << i + 1 << " " << res[i] + 1 << "\n";
    }
    // read the question correctly (is y a vowel?)
    // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
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
