#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define FORD(i, v, u) for (int i = v; i >= u; i--)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define N 1000005
#define mod 1000000007

using namespace std;

int n, k, cnt, dd[N];
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("INP.TXT", "r", stdin);
	cin >> n >> k;
	FOR(i, 1, n) {
		char c; cin >> c;
		if (c == '#') dd[i] = 1, cnt++;
	}
	FOR(i, 1, n) {
		char c; cin >> c;
		if (c == '#') dd[i] = 2, cnt++;
	}
	if (k >= cnt) {
		cout <<n*2 - (n % 2 == 0);
		return 0;
	}
    dd[n+1] = 1;

	pii last = mp(0, 1);
	int res = 0;
	FOR(i, 1, n) {
		int x = i % 2;
		int y = dd[i] - 1;
		if (!dd[i]) {
			res += 2;
			continue;
		}

		if ((x ^ last.F) == (y ^ last.S)) {
			if (k) res += 2, k--;
		}
		else {
			res++;
			last = mp(x, y);
		}
	}
	if ((last.F ^ ((n+1) % 2)) == (last.S ^ (dd[n+1]-1))) {
        if (k) res += 1, k--;
        else res--;
	}
	res += k - (k % 2);
	cout <<res;
}