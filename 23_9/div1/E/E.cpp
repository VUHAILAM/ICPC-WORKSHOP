#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define FORD(i, v, u) for (int i = v; i <= u; i++)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define N 200010
#define mid (r + l)/2
#define ll long long
#define maxc 1000000007
#define int long long

using namespace std;


int n, col[N], row[N], sumcol[N], sumrow[N];
pii a[N];
vector<int> allPoint[N];
vector<int> allx, ally;


struct IntervalTree {
	vector<pii> U[N << 2], V[N << 2];
	int pointer[N << 2];
	
	bool bad(int id, int l1, int l2, int l3) {
		return 1ll*(U[id][l2].S - U[id][l1].S)*(U[id][l1].F - U[id][l3].F) <= 1ll*(U[id][l3].S - U[id][l1].S)*(U[id][l1].F - U[id][l2].F); 
	}
	void makeConvex(int id) {
		for (auto z : V[id]) {
			U[id].PB(z);
			while (U[id].size() >= 3 && bad(id, U[id].size()-3, U[id].size()-2, U[id].size()-1)) 
				U[id].erase(U[id].end()-2);
		}
	}
	void test() {
		V[0].PB(mp(2, 3));
		V[0].PB(mp(2, 3));
		V[0].PB(mp(3, 5));
		V[0].PB(mp(3, 5));
		V[0].PB(mp(4, 1));
		V[0].PB(mp(4, 1));
		V[0].PB(mp(5, 2));
		V[0].PB(mp(5, 2));
		V[0].PB(mp(6, 1));
		V[0].PB(mp(7, 0));
		V[0].PB(mp(7, 0));
		makeConvex(0);
		for (auto z : U[0]) {
			cout <<z.F<<' '<<z.S<<endl;
		}
	}
	ll getVal(int id, int point, int val) {
		return 1ll*U[id][point].F*val + U[id][point].S;
	}
	ll query(int id, int val) {
		while (pointer[id] < U[id].size() - 1 && getVal(id, pointer[id], val) <= getVal(id, pointer[id]+1, val))
			pointer[id]++;
		return getVal(id, pointer[id], val);
	}
	void build(int l, int r, int id) {
		if (l == r) {
			V[id].PB(mp(col[l], sumcol[l]));
			makeConvex(id);
			return;
		}
		build(l, mid, id*2);
		build(mid+1, r, id*2+1);
		V[id].resize(V[id*2].size() + V[id*2+1].size());
		merge(V[id*2].begin(), V[id*2].end(), V[id*2+1].begin(), V[id*2+1].end(), V[id].begin());
		makeConvex(id);
	}
	
	ll getMax(int l, int r, int id, int x, int y, int val) {
		if(x > y) return 0;
		if (l > y || r < x) return 0;
		if (l >= x && r <= y) return query(id, val);
		ll a = getMax(l, mid, id*2, x, y, val);
		ll b = getMax(mid+1, r, id*2+1, x, y, val);
		return max(a, b);
	}
}t;


void setup() {
	cin >> n;
	FOR(i, 1, n) {
		int x, y; cin >> x >> y;
		allx.PB(x); ally.PB(y);
		a[i] = mp(x, y);
	}
}
ll S = 0;
void prepare() {
	allx.PB(-maxc); allx.PB(maxc);
	ally.PB(-maxc); ally.PB(maxc);
	sort(allx.begin(), allx.end());
	sort(ally.begin(), ally.end());
	
	allx.resize(unique(allx.begin(), allx.end()) - allx.begin());
	ally.resize(unique(ally.begin(), ally.end()) - ally.begin());
	
	FOR(i, 1, n) {
		a[i].F = lower_bound(allx.begin(), allx.end(), a[i].F) - allx.begin() + 1;
		a[i].S = lower_bound(ally.begin(), ally.end(), a[i].S) - ally.begin() + 1;
		allPoint[a[i].F].PB(a[i].S);
	}
	
	FOR(i, 1, n) col[a[i].S]++, row[a[i].F]++; 
	//cout << a[i].F << " " << a[i].S << endl;
	
	FOR(i, 1, n) {
		sumcol[a[i].S] += row[a[i].F] - 1;
		sumrow[a[i].F] += col[a[i].S] - 1;	
	}
	
	
	FOR(i, 1, n) {
		S += 1ll*(row[a[i].F]-1)*(col[a[i].S] - 1);
	}
	
}
main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//t.test(); return 0;
	setup();
	prepare();
	
	
	t.build(1, ally.size(), 1);

	vector<pii> order;
	FOR(i, 1, allx.size()) order.PB(mp(row[i], i));
	sort(order.begin(), order.end());
	
	
	ll res = 0;
	for (auto z : order) {
		int idRow = z.S;
		//cout <<idRow<<endl;
		sort(allPoint[idRow].begin(), allPoint[idRow].end());
		//cout <<sumrow[idRow]<<endl;
		int be = 1;
		for (auto k : allPoint[idRow]) {
			//cout <<be <<' '<<k-1<<' '<<z.S<<endl;
			res = max(res, t.getMax(1, ally.size(), 1, be, k-1, row[idRow]) + sumrow[idRow]);
			be = k + 1;
		}
		res = max(res, t.getMax(1, ally.size(), 1, be, ally.size(), row[idRow]) + sumrow[idRow]);
		//cout << sumrow[idRow] << " " << S << endl;
	}
	
	cout <<res + S;
}