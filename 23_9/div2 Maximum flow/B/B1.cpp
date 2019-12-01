#include "bits/stdc++.h"

using namespace std;
int cap[105][105];
int flow[105][105];
vector<int> edg[105];
int indEdg[105][105];
int parent[105];
int n, m, s, t;

bool FindPath() {
    for(int i = 1; i <= n; i++) {
        parent[i] = 0;
    }
    queue<int> q;
    q.push(s);
    parent[s] = n+1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i : edg[u]) {
            if(parent[i] == 0 && cap[u][i]-flow[u][i] != 0) {
                parent[i] = u;
                if(i == t) return true;
                q.push(i);
            }
        }
    }
    return false;
}

void increaseFlow() {
    int delta = INT_MAX;
    int v = t;
    while(v != s) {
        int u = parent[v];
        delta = min(delta, cap[u][v]-flow[u][v]);
        v = u;
    }
    v = t;
    while (v != s)
    {
        int u = parent[v];
        flow[u][v] += delta;
        flow[v][u] -=delta;
        v = u;
    }
}

int maxFlow() {
    while (FindPath())
    {
        increaseFlow();
    }
    int res = 0;
    for(int i : edg[s]) {
        res += flow[s][i];
    }
    return res;
}
vector<int> cut;
void bfs() {
     for(int i = 1; i <= n; i++) {
        parent[i] = 0;
    }
    queue<int> q;
    q.push(s);
    parent[s] = n+1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i : edg[u]) {
            if(parent[i] == 0 && cap[u][i]-flow[u][i] != 0) {
                parent[i] = u; 
                q.push(i);       
            }
            
        }
    }
}

void findCut() {
    bfs();
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j<=n; j++) {
            if(parent[i] && !parent[j] && cap[i][j]) {
                cut.push_back(indEdg[i][j]);
            }
        }
    }
    sort(cut.begin(),cut.end());
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        cin >> cap[u][v];
        cap[v][u] = cap[u][v];
        edg[u].push_back(v); edg[v].push_back(u);
        indEdg[u][v] = indEdg[v][u] = i;
    }
    s = 1, t = n;
    int maxF = maxFlow();
    findCut();
    cout << cut.size() <<" " << maxF <<endl;
    for(int i : cut) {
        cout << i << " ";
    }
    return 0;
}