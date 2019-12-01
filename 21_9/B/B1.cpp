#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define N 60

using namespace std;

int st, n, m, res[N];
int main() {
	cin >> st >> n >> m;
	FOR(i, 1, n) {
		string s; cin >> s;
		if (s[st-1] == '0') continue;
		FOR(j, 1, m) res[j] |= (s[j-1] - '0');
	}
	res[st] = 1;
	int ans = 0;
	FOR(i, 1, m) if (res[i] == 1) ans++;
	cout <<ans-1;
}