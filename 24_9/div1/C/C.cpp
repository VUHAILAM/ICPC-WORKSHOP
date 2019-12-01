#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define N 1000005
#define PB push_back
using namespace std;

int n, k, curTime, tt;
long long a[N], m;
int f[1000001];
int g[1000001];
long long dist(int u, int v) {
    return abs(a[u] - a[v]);
}
void add_edge(int u, int v) {
    f[u] = v;
}
int ans[1000001];
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
//    freopen("INP.TXT", "r", stdin);
    cin >> n >> k >> m;
    FOR(i, 1, n) cin >> a[i];
    int L = 1, R = k+1;
    FOR(i, 1, n) {
        while(R < i) L++, R++;
        while (R < n && dist(i, R+1) < dist(i, L))
            L++, R++;
        if (L == i)
            add_edge(i, R);
        else if (R == i)
            add_edge(i, L);
        else if (dist(i, L) == dist(i, R))
            add_edge(i, L);
        else if (dist(i, L) < dist(i, R))
            add_edge(i, R);
        else add_edge(i, L);
    }
    FOR(i, 1, n) ans[i]=i;
    for(int i=0; i<=__lg(m); i++){
        if((m>>i)&1){
          for(int j=1; j<=n; j++) ans[j]=f[ans[j]];
        }
//        for(int j=1; j<=n; j++) cerr<<f[j]<<" \n"[j==n];
        for(int j=1; j<=n; j++) g[j]=f[f[j]];
        for(int j=1; j<=n; j++) f[j]=g[j];
    }
    FOR(i, 1, n) cout <<ans[i]<<' ';
}