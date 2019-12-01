#include <bits/stdc++.h>
using namespace std;
int n;
vector <int> g[2000001];
int f[2000001];
bool done[2000001];
bool good[2000001];
vector <int> euler;
void dfs(int u){
	done[u]=1;
	euler.push_back(u);
	for(int v: g[u]) if(!done[v]){
		dfs(v);
		euler.push_back(u);
		if(f[v]==0) f[u]++;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cin>>n;
	for(int i=2, a; i<=n; i++){
		cin>>a;
		g[a].push_back(i);
		g[i].push_back(a);
	}
	dfs(1);
	bool first=1;
	int root=1;
	for(auto v: euler){
		if(!first){
			if(f[v]==0) f[root]--;
			if(f[root]==0) f[v]++;
			root=v;
		}
		else first=0;
		good[root]=f[root];
	}
	for(int i=1; i<=n; i++) if(good[i]==0) cout<<i<<'\n';
}