#include <bits/stdc++.h>
using namespace std;
int n;
int a[100001];
long long l;
long long s[100001];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>n;
	int ans=1;
	for(int i=1, u, v; i<=n; i++){
		cin>>u>>v;
		a[i]=min(u, v);
	}
	cin>>l;
	sort(a+1, a+n+1);
	for(int i=1; i<=n; i++) s[i]=s[i-1]+a[i];
	int best=n;
	for(int i=2; i<=n; i++){
		long long rem=l;
		rem-=a[i]/2;
		rem-=a[i-1]/2;
		rem--;
		if(a[i]%2+a[i-1]%2==2) rem--;		
		if(rem<0) break;
		while(s[best]>rem) best--;
		int res=best+2;
		if(best>=i) res--;
		if(best>=i-1) res--;
		ans=max(ans, res); 
	}
	cout<<ans<<'\n';
}	