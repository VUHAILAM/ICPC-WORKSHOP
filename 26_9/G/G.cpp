#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define FORD(i, v, u) for (int i = v; i >= u; i--)
#define PB push_back

using namespace std;

int n;
vector<int> ans, res;
void solve(string s) {
	//cerr<<s<<endl;
	int cnt = 0;
	int pos = 0;
	FOR(i, 1, n)
		if (s[i] == '1') cnt++, pos = i;
	if (cnt == 0) return;
	if (cnt == 1) {
		if (n % 2 == 1) {
			for (int j = pos+1; j < pos+n; j += 2)
				ans.PB(j);
			for (int j = 2; j < n; j += 2)
				ans.PB(j);
			return;
		}

	}
	//if (cnt == 2)
    {
        FOR(i, 1, n)
            FOR(j, i+1, i+n-1) {
                if (s[i] == '0' || s[j] == '0') continue;
                if ((j-i) % 2 == 0) break;
                if (i == j+1) {
                    ans.PB(i);
                }
                else {
                    for (int h = i+1; h < j; h += 2)
                        ans.PB(h);
                    for (int h = i; h < j; h += 2)
                        ans.PB(h);
                }

                s[i] = s[j] = '0';
                if (i <= n) s[i+n] = '0';
                else s[i-n] = '0';
                if (j <= n) s[j+n] = '0';
                else s[j-n] = '0';
                solve(s);
                return;

            }
	}
	FOR(i, 1, n) {
		if (s[i] == '1') {
			if (i <= 2 || s[i-2] == '1') continue;
			int jj;
			//cout <<i<<" dfssdfa"<<endl;
			for (jj = i-2; jj >= 1 && s[jj] == '0'; jj -= 2)
				ans.PB(jj);
			for (int j = i-1; j >= 1 && s[j-1] == '0'; j -= 2)
				ans.PB(j);
			s[i] = s[i+n] = '0';
			s[jj+2] = s[jj+n+2] = '1';
			solve(s);
			return;
		}
	}
	return;
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	//freopen("INP.TXT", "r", stdin);
	string A, B;
	string cA, cB;
	cin >> A >> B; cA = A; cB = B;
	n = A.size();
	FOR(i, 0, n-1) A.PB(A[i]);
	A = " " + A;
	solve(A);
	for (auto x : ans) res.PB(x);


	ans.clear();
	FOR(i, 0, n-1) B.PB(B[i]);
	B = " " + B;
	solve(B);
	reverse(ans.begin(), ans.end());

	for (auto x : ans) res.PB(x);

	cout <<res.size() <<'\n';
	for (auto x : res) cout <<(x-1) % n<<'\n';

    /*for (auto y : res) {
        int x = (y-1) % n;
        if (cA[x] == cA[(x+1) % n]) {
            cA[x] = '1' + '0' - cA[x];
            cA[(x+1) % n] = '1' + '0' - cA[(x+1) % n];
        }
        else {
            cout <<"noooo";
            exit(0);
        }
        cerr<<cA<<endl;
    }
    cout <<"GOODDDDDD";*/
}
