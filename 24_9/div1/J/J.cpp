#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define PB push_back
#define N 400005
using namespace std;

int n, m, cnt1[3], cnt2[3], dd[N];
long long res = 0;
vector<int> a[N];
void BFS(int u) {
    queue<int> q;
    memset(dd, -1, sizeof dd);
    q.push(u);
    dd[u] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dd[u] == 2) continue;
        for (auto v : a[u]) {
            if (dd[v] != -1) continue;
            dd[v] = dd[u] + 1;
            q.push(v);
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("INP.TXT", "r", stdin);
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        a[u].PB(v);
        a[v].PB(u);
    }
    memset(dd, -1, sizeof dd);
    BFS(1);
    FOR(i, 1, n)
        if (dd[i] != -1) cnt1[dd[i]]++;
    memset(dd, -1, sizeof dd);
    BFS(2);
    FOR(i, 1, n)
        if (dd[i] != -1) cnt2[dd[i]]++;

    FOR(i, 0, 1) {
        res += 1ll*(cnt1[i]-1)*cnt1[i]/2;
        res += 1ll*(cnt2[i]-1)*cnt2[i]/2;
    }
    FOR(i, 1, 2) {
        res += 1ll*cnt1[i]*cnt1[i-1];
        res += 1ll*cnt2[i]*cnt2[i-1];
    }
    //cout <<res<<endl;
    int sum = 0;
    FOR(i, 0, 1)
        sum += cnt1[i] + cnt2[i];
    res += 1ll*(n - sum)*(n-sum-1)/2;
    //cout <<res<<endl;
    sum += cnt1[2] + cnt2[2];
    res += 1ll*(n-sum)*max(cnt1[1], cnt2[1]);
    cout <<res-m;
}