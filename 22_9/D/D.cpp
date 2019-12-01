#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define FORD(i, v, u) for (int i = v; i >= u; i--)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define N 100005
#define MAGIC 500
#define ll long long

using namespace std;

struct BIT {
	int sumcnt;
	long long sumsum; 
	pair < ll, int > sum[N];
	
	void updSum(int x, ll val, int cnt) {
		if(x == 0) return;
		for (; x < N; x += (x & -x)) {
			sum[x].first += val;
			sum[x].second += cnt;
		}
	}
	void upd(int x, ll summ, int cntt) {
		updSum(x, summ, cntt);
		sumsum += summ;
		sumcnt += cntt;
	}
	
	pair < ll, int > getSum(int x) {
		pair < ll, int > ans = {0, 0};
		for (; x; x -= (x & -x)) {
			ans.first += sum[x].first;
			ans.second += sum[x].second;
		}
		return ans;
	}

	void insert(int x, ll val) {
		upd(x, val, 1);
	}
	
	void erase(int x, ll val) {
		upd(x, -val, -1);
	}
	
	ll query(int x, ll val) {
		auto p = getSum(x);
		int cntt = p.second;
		ll summ = p.first;
		int cntt2 = sumcnt - cntt;
		ll summ2 = sumsum - summ;
		return 1ll*val*cntt - summ + summ2 - 1ll*val*cntt2;
	}
}t;

int n, numQ, a[N], b[N];
vector<int> block[(N / MAGIC) + 5];
ll sum[(N / MAGIC) + 5][N], res[N];
vector<pair<pii, int> > q[N];


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> n >> numQ;
	vector<int> allX;
	FOR(i, 1, n) cin >> a[i], allX.PB(a[i]);
	sort(allX.begin(), allX.end());
	allX.resize(unique(allX.begin(), allX.end()) - allX.begin());
	
	FOR(i, 1, n) b[i] = lower_bound(allX.begin(), allX.end(), a[i]) - allX.begin() + 2;
	
	
	FOR(i, 1, n) block[i/MAGIC].PB(i);
	
	FOR(i, 0, n / MAGIC + 1) {
		for (auto x : block[i])
			t.insert(b[x], a[x]);
		FOR(j, 1, n) {
			sum[i][j] = sum[i][j-1] + t.query(b[j], a[j]);
		}
		for(int x : block[i]) {
			t.erase(b[x], a[x]);
		}
	}
	
	
	FOR(i, 1, numQ) {
		int u, v, x, y; cin >> u >> v >> x >> y;
		
		FOR(bl, 0, n / MAGIC + 1) {
			if (block[bl].empty()) continue;
			int l = block[bl].front();
			int r = block[bl].back();
			
			if (l > v || r < u) continue;
			if (u <= l && v >= r) {
				res[i] += sum[bl][y] - sum[bl][x-1];
				continue;
			}
			
			l = max(l, u);
			r = min(r, v);
			q[y].PB(mp(mp(l, r), i));
			q[x-1].PB(mp(mp(l, r), -i));
		}
	}
	FOR(i, 0, n) {
		if (i) t.insert(b[i], a[i]);
		for (auto z : q[i]) {
			int l = z.F.F;
			int r = z.F.S;
			int id = abs(z.S);
			int sign = id/z.S;
			
			FOR(j, l, r)
				res[id] += 1ll*sign*t.query(b[j], a[j]);
		}
	}
	FOR(i, 1, numQ) cout <<res[i]<<'\n';
}