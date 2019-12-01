#include <bits/stdc++.h>
using namespace std;
int n, m;
int r[10001];
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
vector <int> f[10001];
int root(int u){
	if(r[u]<0) return u;
	return r[u]=root(r[u]);
}
void unite(int u, int v){
	u=root(u);
	v=root(v);
	if(u==v) return;
	if(r[u]>r[v]) swap(u, v);
	r[u]+=r[v];
	for(auto x: f[v]) f[u].push_back(x);
	r[v]=u;
}
priority_queue <pair <int, int>> s;
int ask(int x){
	cout<<"? "<<x<<endl;
	int res=0;
	cin>>res;
	return res;
}
void solve(){
	cin>>n>>m;
	while((!s.empty())) s.pop();
	for(int i=1; i<=n; i++){
		r[i]=-1;
		s.push(make_pair(-1, i));
		f[i].clear();
		f[i].push_back(i);
	}
	while(s.size()>1){
		auto x=s.top();
		s.pop();
		// cerr<<x.first<<' ';
		// cerr<<x.second<<'\n';
		if(root(x.second)!=x.second) continue;
		if(x.first!=r[x.second]) continue;
		// cerr<<x.first<<' ';
		// cerr<<x.second<<'\n';
		int found=0;
		while(!f[x.second].empty()){
			int i=rng()%f[x.second].size();
			swap(f[x.second][i], f[x.second].back());
			int res=ask(f[x.second].back());
			if(res==-1) f[x.second].pop_back();
			else if(root(res)==x.second) continue;
			else{
				found=res;
				break;
			}
		}
		if(found==0){
			cout<<'-'<<endl;
			return;
		}
		unite(x.second, found);
		s.push(make_pair(r[root(found)], root(found)));
		// cerr<<s.size()<<'\n';
	}
	cout<<'+'<<endl;
}
int main(){
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL); cout.tie(NULL);
	int t;
	cin>>t;
	while(t--) solve();
}	