#include <bits/stdc++.h>
using namespace std;
void solve(){
	long long a, y;
	cin>>a>>y;
	if(y==0){
		cout<<"Yes\n";
		return;
	}
	while(a){
		long long x=a;
		while(x){
			long long t=x;
			while(t<y) t*=2;
			if(t==y){
				cout<<"Yes\n";
				return;
			}
			x/=2;
		}
		a-=1LL<<__lg(a);
	}
	cout<<"No\n";
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int t;
	cin>>t;
	while(t--) solve();
}