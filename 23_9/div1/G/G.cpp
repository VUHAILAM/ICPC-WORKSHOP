#include <bits/stdc++.h>
using namespace std;
int n, m;
bool good[1000001];
void fail(){
	cout<<"No\n";
	exit(0);
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>n>>m;
	for(int i=1, x, y; i<=m; i++){
		cin>>x>>y;
		if(x>y) fail();
		if(x+1==y) good[x]=1;
	}
	cerr<<"OK\n";
	for(int i=1; i<n; i++) if(!good[i]) fail();
	cout<<"Yes\n";
}