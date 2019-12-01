#include <bits/stdc++.h>
using namespace std;

const int N = 1010;

int n, m, s;
int deg[N];
int ans[N];
vector < int > g[N];
vector < int > adj[N];

int erased, to;
bool visited[N];

bool dfs(int v) {
	if(v == to) return true;
	if(v == erased) return false;
	for(int s : g[v]) if(!visited[s]){
		visited[s] = 1;
		if(dfs(s)) return true;
	}
	return false;
}

map<pair<int, int>, int> dd;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	while(cin >> n >> m >> s) {
		if(n == 0) break;
		for(int i = 1; i <= m; ++i) {
			int u, v; cin >> u >> v;
			if (u == v) continue;
			if (dd[make_pair(u, v)]) continue;
			dd[make_pair(u, v)] = 1;
			g[u].push_back(v);
		}
		
		for(int v = 1; v <= n; ++v) {
			for(int w : g[v]) {
				memset(visited, false, sizeof visited);
				erased = w;
				to = v;
				if(dfs(s)) {
					adj[v].push_back(w);
					++deg[w];
				}
			}
		}
		
		vector < int > qu;
		for(int v = 1; v <= n; ++v) if(!deg[v]) qu.push_back(v);
		
		int cnt = 0;
		
		while(qu.size()) {
			int v = qu.back(); qu.pop_back();
			ans[v] = ++cnt;
			for(int s : adj[v]) if(--deg[s] == 0) {
				qu.push_back(s);
			}
		}
		
		bool possible = true;
		
		for(int i = 1; i <= n; ++i) {
			if(deg[i]) possible = false;
			if(!ans[i]) ans[i] = ++cnt;
		}
		
		if(!possible) cout << "No solution" << endl;
		else {
			for(int i = 1; i <= n; ++i) cout << ans[i] << " ";
			cout << endl;
		}
		
		for(int i = 1; i <= n; ++i) {
			deg[i] = ans[i] = 0;
			g[i].clear();
			adj[i].clear();
		}	
		dd.clear();	
	}
	
	return 0;
}	