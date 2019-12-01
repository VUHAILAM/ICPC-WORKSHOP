#include <bits/stdc++.h>
using namespace std;
long long n, d;
int main(){
	cin>>n>>d;
	int ans=0;
	while(d){
		ans++;
		if(n%d==0) break;
		d=d-n%d;
	}
	cout<<ans<<'\n';
}