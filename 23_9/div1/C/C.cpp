#include <bits/stdc++.h>
using namespace std;
int n, m, k;
vector <pair <int, int>> g[200001];
vector <int> v;
class cmp{
public:
	bool operator ()(pair <int, int> A, pair <int, int> B){
		return (A.second>B.second);
	}
};
pair <int, int> ans[200001];
pair <int, int> f[200001];
bool inq[200001];
queue <int> q;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m>>k;
	for(int i=1, a, b, c; i<=m; i++){
		cin>>a>>b>>c;
		g[a].push_back({b, c});
		g[b].push_back({a, c});
	}
	v.resize(k);
	for(auto &x: v) cin>>x;
	for(auto &x: v) ans[x]={2.1e9, -1};
	for(int i=1; i<=n; i++) shuffle(g[i].begin(), g[i].end(), rng);
	for(int lg=0; lg<=__lg(k-1); lg++){
		while(!q.empty()) q.pop();
		for(int j=1; j<=n; j++) f[j]={2.1e9, 0};
		for(int j=0; j<k; j++) if(((j>>lg)&1)==0){
			f[v[j]]={0, v[j]};
			q.push(v[j]);
		}
		while(!q.empty()){
			auto p=q.front();
			q.pop();
			inq[p]=0;
			for(auto v: g[p]) if(f[v.first].first>f[p].first+v.second){
				f[v.first].first=f[p].first+v.second;
				f[v.first].second=f[p].second;
				if(!inq[v.first]){
					inq[v.first]=1;
					q.push(v.first);
				}
			}
			else if(f[v.first].first==f[p].first+v.second){
				f[v.first].second=min(f[v.first].second, f[p].second);
			}
		}
		for(int j=0; j<k; j++) if(((j>>lg)&1)==1) ans[v[j]]=min(ans[v[j]], f[v[j]]);
	}
	for(int lg=0; lg<=__lg(k-1); lg++){
		while(!q.empty()) q.pop();
		for(int j=1; j<=n; j++) f[j]={2.1e9, 0};
		for(int j=0; j<k; j++) if(((j>>lg)&1)==1){
			f[v[j]]={0, v[j]};
			q.push(v[j]);
		}
		while(!q.empty()){
			auto p=q.front();
			q.pop();
			inq[p]=0;
			for(auto v: g[p]) if(f[v.first].first>f[p].first+v.second){
				f[v.first].first=f[p].first+v.second;
				f[v.first].second=f[p].second;
				if(!inq[v.first]){
					inq[v.first]=1;
					q.push(v.first);
				}
			}
			else if(f[v.first].first==f[p].first+v.second){
				f[v.first].second=min(f[v.first].second, f[p].second);
			}
		}
		for(int j=0; j<k; j++) if(((j>>lg)&1)==0) ans[v[j]]=min(ans[v[j]], f[v[j]]);
	}
	for(auto &x: v) cout<<ans[x].second<<'\n';
}	
