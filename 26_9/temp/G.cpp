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
const int N = 107;
int n;
char s1[N], s2[N];

void condense(char s[N], vec<int> &op) {
    int j;
    FOR(i, 0, n) {
        if (s[i] == '1') {
            j = (i + 1) % n;
            if (s[j] == '1') {
                op.pb(i);
                s[i] = s[j] = '0';
                i++;
            }
        }
    }
    // cerr << "\n";
    // if (s[0] == '1' and s[n - 1] == '1') {
    //     s[0] = s[n - 1] = '0';
    //     op.pb(n - 1);
    // }
    FOR(i, 0, n) {
        if (s[i] == '1') {
            for (j = i - 1; j >= 0; j -= 2) {
                if (s[j] == '1') {
                    s[j] = '0';
                    op.pb(j);
                    break;
                }
                if (j >= 1) {
                    if (s[j - 1] == '1') {
                        break;
                    }
                    s[j + 1] = '0';
                    s[j - 1] = '1';
                    op.pb(j - 1);
                    op.pb(j);
                }
            }
        }
    }
}

void solve()
{
    scanf("%s %s", s1, s2);
    n = strlen(s1);
    vec<int> op1, op2;
    condense(s1, op1);
    condense(s2, op2);
    
    int m = op1.size() + op2.size();
    printf("%d\n", m);
    for (int i : op1) printf("%d\n", i);
    reverse(op2.begin(), op2.end());
    for (int i : op2) printf("%d\n", i);
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
