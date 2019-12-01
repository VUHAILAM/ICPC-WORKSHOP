#include <bits/stdc++.h>
using namespace std;
int n, m;
vector <int> pos[1000001];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>m;
	for(int i=1, a; i<=m; i++){
		cin>>a;
		pos[a].push_back(i);
	}
	cin>>n;
	for(int i=1, k, m; i<=n; i++){
		cin>>k;
		int now=0;
		bool bad=0;
		for(int j=1; j<=k; j++){
			cin>>m;
			if(bad) continue;
			if(pos[m].empty()){
				bad=1;
				continue;
			}
			if(pos[m].back()<=now){
				bad=1;
				continue;
			}
			now=*upper_bound(pos[m].begin(), pos[m].end(), now);
		}
		if(bad) cout<<"NIE\n";
		else cout<<"TAK\n";
	}
}	