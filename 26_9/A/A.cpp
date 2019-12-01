#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define FORD(i, v, u) for (int i = v; i >= u; i--)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define N 35005
#define maxc 100000007
#define ll long long

using namespace std;

void inline MIN(ll &A, ll B) {A = min(A, B);}

int n, k;
vector<int> a[N];
long long dp[2][1002];
int main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("1.inp", "r", stdin);
	cin >> n >> k;
	FOR(i, 1, n)  {
		a[i].resize(2*k+1);
		FOR(j, 0, 2*k) cin >> a[i][j];
	}
	random_shuffle(a+1, a+n+1);
	random_shuffle(a+1, a+n+1);

	bool flag = 0;
	FOR(i, 0, 1)
		FOR(j, 0, 1000) dp[i][j] = 1ll*maxc*maxc;
	dp[0][500] = 0;
	FOR(i, 1, n) {
		bool newFlag = flag ^ 1;
		FOR(j, 0, 1000) dp[newFlag][j] = 1ll*maxc*maxc;
		FOR(j, 0, 1000)
			FOR(h, 0, 2*k) {
				int preS = (j-500) + (h-k) + 500;
				if (preS < 0 || preS > 1000) continue;
				MIN(dp[newFlag][j], dp[flag][preS] + a[i][h]);
			}
		swap(flag, newFlag);
	}
	cout <<dp[flag][500];
}