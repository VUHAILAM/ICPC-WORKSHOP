#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define N 105

using namespace std;
char c[N][N];

int main() {
	
	int n, m; cin >> n >> m;
	FOR(i, 1, n) 
		FOR(j, 1, m) cin >> c[i][j];
	
	FOR(i, 1, n) {
		FOR(j, 1, m) {
				if (c[i][j] == 'L') continue;
				if (c[i-1][j] == 'B' || c[i][j-1] == 'B') c[i][j] = 'F';
				else c[i][j] = 'B';
		}
	}
	FOR(i, 1, n) {
		FOR(j, 1, m) cout <<c[i][j];
		cout <<'\n';
	}
}