#include <bits/stdc++.h>

using namespace std;

const int N = 200020;
typedef bitset < 77 > bs;

int n, m;
bs a[N];
bs test[77];
bs test2[77];
bs basic[77];
int neg[77];
int pos[77];
bs building, nwbuilding, temp;

long long pw3[N];
pair < int, int > w[N];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); 
	
	memset(neg, -1, sizeof neg);
	memset(pos, -1, sizeof pos);
	
	cin >> n >> m;
	
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < m; ++j) {
			char c; cin >> c;
			a[i][j] = (c == '1');
		}
	}
	
	pw3[0] = 1;
	for(int i = 1; i < 77; ++i) pw3[i] = pw3[i - 1] * 3;
	
	vector < int > perm;
	
	for(int i = 0; i < m; ++i) {
		int x, y;
		cin >> x >> y;
		w[i] = make_pair(x, y);
		perm.push_back(i);
		
		if(x == -1) neg[y] = i;
		else pos[y] = i;
	}
	
	sort(perm.begin(), perm.end(), [&](int x, int y){
		return make_pair(w[x].second, w[x].first) > make_pair(w[y].second, w[y].first);
	});
	
	for(int i = 1; i <= n; ++i) {
		for(int r : perm) {
			if(!a[i][r]) continue;
			if(!basic[r][r]) { 
				basic[r] = a[i];
				break;
			}
			a[i] ^= basic[r];
		}
	}
	
	
	long long ans = 0;
	vector < int > req, tempreq;
	
	for(int i = 35; i >= 1; --i) {
		if(pos[i] != -1 && neg[i] == -1) {
			for(int it = m - 1; it >= 0; --it) test[it] = basic[it];
			nwbuilding = building;
			nwbuilding[pos[i]] = 1;
			
			tempreq = req;
			tempreq.emplace_back(pos[i]);
			
			temp.reset();
			
			bool flag = true;
			for(int id : tempreq) {
				if(temp[id] != nwbuilding[id]) {
					if(!test[id][id]) {
						flag = false;
						break;
					}
					temp ^= test[id];
				}
			}
			
			if(flag) {
				for(int it = m - 1; it >= 0; --it) basic[i] = test[i];
				building = nwbuilding;
				req = tempreq;
				ans += pw3[i];
			}
			
			continue;
		}
		if(neg[i] != -1 && pos[i] == -1) {
			for(int it = m - 1; it >= 0; --it) test[it] = basic[it];
			nwbuilding = building;
			nwbuilding[neg[i]] = 0;
			
			tempreq = req;
			tempreq.emplace_back(neg[i]);
			
			temp.reset();
			
			bool flag = true;
			for(int id : tempreq) {
				if(temp[id] != nwbuilding[id]) {
					if(!test[id][id]) {
						flag = false;
						break;
					}
					temp ^= test[id];
				}
			}
			
			if(flag) {
				for(int it = m - 1; it >= 0; --it) basic[it] = test[it];
				building = nwbuilding;
				req = tempreq;
			}
			else ans -= pw3[i];
			
			continue;
		}
		if(neg[i] != -1 && pos[i] != -1) {
			
			/// only pos but not neg
			{
				for(int it = m - 1; it >= 0; --it) test[it] = basic[it];
				nwbuilding = building;
				nwbuilding[pos[i]] = 1;
				nwbuilding[neg[i]] = 0;
				
				tempreq = req;
				tempreq.emplace_back(pos[i]);
				tempreq.emplace_back(neg[i]);
				
				temp.reset();
				
				
				
				bool flag = true;
				for(int id : tempreq) {
					if(temp[id] != nwbuilding[id]) {
						if(!test[id][id]) {
							flag = false;
							break;
						}
						temp ^= test[id];
					}
				}
							
				if(flag) {
					for(int it = m - 1; it >= 0; --it) basic[it] = test[it];
					building = nwbuilding;
					req = tempreq;
					ans += pw3[i];
					continue;
				}
			}
			
			/// merge pos[i] and neg[i]
			
			{
				for(int it = m - 1; it >= 0; --it) {
					test[it] = basic[it];
					if(test[it][neg[i]]) {
						test[it].flip(pos[i]);
						test[it].flip(neg[i]);
					}
					test2[it].reset();
				}
				
				for(int it = m - 1; it >= 0; --it) {
					for(int j : perm) {
						if(!test[it][j]) continue;
						if(!test2[j][j]) {
							test2[j] = test[it];
							break;
						}
						test[it] ^= test2[j];
					}
				}
				
				for(int it = m - 1; it >= 0; --it) test[it] = test2[it];


				nwbuilding = building;
				nwbuilding[pos[i]] = 0;
				
				tempreq = req;
				tempreq.emplace_back(pos[i]);
				
				temp.reset();
				
				bool flag = true;
				for(int id : tempreq) {
					if(temp[id] != nwbuilding[id]) {
						if(!test[id][id]) {
							flag = false;
							break;
						}
						temp ^= test[id];
					}
				}
				
				if(flag) {
					for(int i = m - 1; i >= 0; --i) basic[i] = test[i];
					building = nwbuilding;
					req = tempreq;
					continue;
				}
			}
			ans -= pw3[i];
			continue;
		}
	}
	
	cout << ans << endl;
	
	return 0;
}