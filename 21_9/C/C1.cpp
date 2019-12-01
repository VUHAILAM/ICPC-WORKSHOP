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
				if (c[i][j] != 'F') continue;
				if (c[i+1][j] == 'F') c[i+1][j] = 'G';
				if (c[i][j+1] == 'F') c[i][j+1] = 'G';
				
				c[i][j] = 'B';
		}
	}
	FOR(i, 1, n) {
		FOR(j, 1, m) if (c[i][j] == 'G') cout <<'F';
		else cout <<c[i][j];
		cout <<'\n';
	}
}