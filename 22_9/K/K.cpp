#include <bits/stdc++.h>
using namespace std;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int a, b;
	cin>>a>>b;
	int ans=a*b*4, mx=a*b*4;
	for(int i=0; i<mx; i++){
		vector <int> x;
		for(int j=0; j<a; j++) x.push_back(j*(mx/a));
		for(int j=0; j<b; j++) x.push_back((i+j*(mx/b))%mx);
		sort(x.begin(), x.end());
		x.push_back(mx);
		int low=mx, high=0;
		for(int j=0; j+1<x.size(); j++){
			int sz=x[j+1]-x[j];
			low=min(low, sz);
			high=max(high, sz);
		}
		ans=min(ans, high-low);
	}
	int d=__gcd(ans, mx);
	ans/=d;
	mx/=d;
	cout<<ans<<" / "<<mx<<'\n';
}	