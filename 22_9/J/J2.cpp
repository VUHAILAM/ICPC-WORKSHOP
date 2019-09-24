
#include <bits/stdc++.h>
using namespace std;

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
const int N = 1e5 + 7;

int a[N];

void solve()
{
    int n;
    scanf("%d", &n);
    int x, y, len;
    FOR(i, 0, n)
    {
        scanf("%d %d", &x, &y);
        a[i] = min(x, y) * 2;
    }
    sort(a, a + n);
    scanf("%d", &len);
    len *= 2;
    if (n == 1)
    {
        printf("1");
        return;
    }
    if (n == 2)
    {
        printf("%d", (len <= (a[0] + a[1]) / 2? 1 : 2));
        return;
    }

    int sum = 0, cur;
    FOR(i, 1, n)
    {
        // debug3(i, a[i - 1], a[i]);
        cur = (a[i - 1] + a[i]) / 2;
        // debug3(sum, cur, len);
        if (len <= sum + cur)
        {
            printf("%d", i);
            return;
        }
        sum += a[i - 1];
    }
    printf("%d", n);
    // read the question correctly (is y a vowel?)
    // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main()
{
    //auto beginProgram = chrono::steady_clock::now();
    {
        solve();
    }
    //auto endProgram = chrono::steady_clock::now();

    return 0;
}
