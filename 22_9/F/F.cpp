#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define N 100005
#define maxc 1000000007
#define ll long long

using namespace std;

struct IntervalTree {
	int t[N << 2], lazy[N << 2];
	
	void push(int l, int r, int id) {
		if (lazy[id] == 0) return;
		int z = lazy[id]; lazy[id] = 0;
		t[id] += z;
		if (l == r) return;
		lazy[id*2] += z;
		lazy[id*2+1] += z;
	}
	void update(int l, int r, int id, int x, int y, int val) {
		push(l, r, id);
		if (l > y || r < x) return;
		if (l >= x && r <= y) {
			lazy[id] += val;
			push(l, r, id);
			return; 
		}
		int mid = (r + l)/2;
		update(l, mid, id*2, x, y, val);
		update(mid+1, r, id*2+1, x, y, val);
		t[id] = min(t[id*2], t[id*2+1]);
	}
	
	int getMin(int l, int r, int id, int x, int y) {
		push(l, r, id);
		if (l > y || r < x) return maxc;
		if (l >= x && r <= y) return t[id];
		int mid = (r + l)/2;
		int a = getMin(l, mid, id*2, x, y);
		int b = getMin(mid+1, r, id*2+1, x, y);
		return min(a, b);
	}
}t;

int n, val[N], lim[N];
vector<int> g[N];
pii a[N];

int pa[N], sz[N], spe[N], tt, head[N], curChain = 1, chainInd[N], posInBase[N];
void preDFS(int u) {
	sz[u] = 1, spe[u] = 0;
	for (auto v : g[u]) {
		pa[v] = u;
		preDFS(v);
		if (sz[v] > sz[spe[u]]) spe[u] = v;
		sz[u] += sz[v];
	}
}

void HLD(int u) {
	if (head[curChain] == 0) head[curChain] = u;
	chainInd[u] = curChain;
	posInBase[u] = ++tt;
	t.update(1, n, 1, tt, tt, lim[u]);
	
	if (spe[u]) {
		HLD(spe[u]);
		for (auto v : g[u])
			if (v != spe[u]) {
				curChain++;
				HLD(v);
			}
	}
}

int getMinLimit(int u) {
	int ans = maxc;
	while (u != 0) {
		int v = head[chainInd[u]];
		ans = min(ans, t.getMin(1, n, 1, posInBase[v], posInBase[u]));
		u = pa[v];
	}
	return ans;
}
void updateLimit(int u, int limit) {
	while (u != 0) {
		int v = head[chainInd[u]];
		t.update(1, n, 1, posInBase[v], posInBase[u], -limit);
		u = pa[v];
	}
}
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> lim[1];
	n++;
	FOR(i, 2, n) {
		int v; cin >> val[i] >> v >> lim[i];
		v++;
		g[v].PB(i);
	}
	preDFS(1);
	HLD(1);
	FOR(i, 1, n) a[i] = mp(val[i], i);
	sort(a+1, a+n+1);
	reverse(a+1, a+n+1);
	
	ll res = 0;
	FOR(i, 1, n) {
		int u = a[i].S;
		int limit = getMinLimit(u);
		res += 1ll*limit*val[u];
		updateLimit(u, limit);
	}
	cout <<res;
}