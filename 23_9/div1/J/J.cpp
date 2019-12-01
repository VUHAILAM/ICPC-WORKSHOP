#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define FORD(i, v, u) for (int i = v; i >= u; i--)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define N 220005
#define LN 19
#define MM 10000004
#define maxc 1000000007

using namespace std;

struct edge {
	int u, v, c, f;
	edge(int _u=0, int _v=0, int _c=0, int _f=0) : u(_u), v(_v), c(_c), f(_f) {}
}e[MM];
vector<int> g[N];
int S, T, cnt = 0, dd[N], cur_time, pos[N], d[N];

void add_edge(int u, int v, int c) {
	if (u == 0 || v == 0) return;
	e[cnt] = edge(u, v, c, 0);
	g[u].PB(cnt++);
	e[cnt] = edge(v, u, 0, 0);
	g[v].PB(cnt++);
}

bool BFS() {
	dd[S] = ++cur_time;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		pos[u] = 0;
		for (auto id : g[u]) {
			int v = e[id].v;
			if (dd[v] == cur_time || e[id].c == e[id].f) continue;
			dd[v] = cur_time;
			q.push(v);
			d[v] = d[u] + 1;
		}
	}
	return (dd[T] == cur_time);
}
int DFS(int u, int delta) {
	if (u == T || delta == 0) return delta;
	for (; pos[u] < g[u].size(); pos[u]++) {
		int id = g[u][pos[u]];
		int v = e[id].v;
		if (d[v] != d[u] + 1 || e[id].c == e[id].f)
			continue;
		if (int x = DFS(v, min(delta, e[id].c - e[id].f))) {
			e[id].f += x;
			e[id^1].f -= x;
			return x;
		}
	}
	return 0;
}

int MaxFlow() {
	int max_flow = 0;
	while (BFS()) {
		while (int x = DFS(S, maxc)) max_flow += x;
		/*if (max_flow > 0) {
            return max_flow;
		}*/
	}
	return max_flow;
}

int n, m, numNode, pa[N][LN], ga[N][LN], h[N], w[N];
vector<int> a[N];
int tin[N], tout[N], tt;

void preDFS(int u, int p) {
    tin[u] = ++tt;
	for (auto v : a[u]) {
		if (v == p) continue;
		h[v] = h[u] + 1;
		pa[v][0] = u;
		FOR(i, 1, LN-1)
			pa[v][i] = pa[pa[v][i-1]][i-1];
		preDFS(v, u);
	}
	tout[u] = tt;
}
bool isAnc(int u, int v) {
    return (tin[u] <= tin[v] && tout[u] >= tout[v]);
}
int LCA(int u, int v) {
	if (h[u] > h[v]) swap(u, v);
	int delta = h[v] - h[u];
	FOR(i, 0, LN-1)
		if ((delta >> i) & 1) v = pa[v][i];
	if (u == v) return u;
	FORD(i, LN-1, 0)
		if (pa[u][i] != pa[v][i]) {
			u = pa[u][i];
			v = pa[v][i];
		}
	return pa[u][0];
}
void setup() {
	cin >> n >> m;
	FOR(i, 1, n) cin >> w[i];
	FOR(i, 2, n) {
		int u, v; cin >> u >> v;
		a[u].PB(v);
		a[v].PB(u);
	}
}
void buildGraph() {
	numNode = m+n+2;
	S = 1, T = 2;
	FOR(i, 1, n)
		add_edge(i+2, T, w[i]);

    FOR(u, 1, n) FOR(i, 0, LN-1) ga[u][i] = ++numNode;
	FOR(u, 1, n) {
		if (pa[u][0])
            add_edge(ga[u][1], pa[u][0]+2, maxc);
		add_edge(ga[u][1], u+2, maxc);
		FOR(j, 2, LN-1) {
			add_edge(ga[u][j], ga[u][j-1], maxc);
			add_edge(ga[u][j], ga[pa[u][j-1]][j-1], maxc);
		}
	}
	FOR(i, 1, m) {
		int u, v, ww; cin >> u >> v >> ww;
		add_edge(S, n+i+2, ww);

		int lca = LCA(u, v);

        int delta = h[u] - h[lca] + 1;
        FORD(j, LN-1, 0)
            if ((delta >> j) & 1) {
                if (j == 0) add_edge(n+i+2, u+2, maxc);
                else add_edge(n+i+2, ga[u][j], maxc);
                u = pa[u][j];
            }
        delta = h[v] - h[lca] + 1;
        FORD(j, LN-1, 0)
            if ((delta >> j) & 1) {
                if (j == 0) add_edge(n+i+2, v+2, maxc);
                else add_edge(n+i+2, ga[v][j], maxc);
                v = pa[v][j];
            }
	}
}
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("INP.TXT", "r", stdin);
	setup();
	preDFS(1, -1);

	buildGraph();

	cout <<MaxFlow();
}