#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)

using namespace std;

int n, m;
string s, t;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin >> s >> t;
	n = s.size(); s = " " + s;
	m = t.size(); t = " " + t;
	
	int pos = 1, last = 1;
	FOR(i, 1, m) {
		if (t[i] == s[pos] && (i-last) % 2 == 0) {
			last = i+1;
			pos++;
		}
		if (pos == n+1 && (m - last + 1) % 2 == 0) {
			cout <<"YES";
			return 0;
		}
	}
	cout <<"NO";
}	