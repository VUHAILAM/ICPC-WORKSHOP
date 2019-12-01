#include <bits/stdc++.h>
using namespace std;
using ll=long long;
int n;
int a[200002];
ll mod[]={999727999, 988244353};
ll base[]={1000007, 237489};
ll p[2][200002];
ll hl[2][200002];
ll hr[2][200002];
ll _ghl(int b, int l, int r){
	ll res=(hl[b][r]-hl[b][l-1]*p[b][r-l+1])%mod[b];
	if(res<0) res+=mod[b];
	return res;
}
ll _ghr(int b, int l, int r){
	ll res=(hr[b][l]-hr[b][r+1]*p[b][r-l+1])%mod[b];
	if(res<0) res+=mod[b];
	return res;
}
pair <ll, ll> ghl(int l, int r){
	return {_ghl(0, l, r), _ghl(1, l, r)};
}
pair <ll, ll> ghr(int l, int r){
	return {_ghr(0, l, r), _ghr(1, l, r)};
}
int ans=0;
vector <int> bestk;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>n;
	for(int i=1; i<=n; i++) cin>>a[i];
	for(int b=0; b<=1; b++){
		p[b][0]=1;
		for(int i=1; i<=n; i++){
			p[b][i]=(p[b][i-1]*base[b])%mod[b];
		}
		for(int i=1; i<=n; i++) hl[b][i]=(hl[b][i-1]*base[b]+a[i])%mod[b];
		for(int i=n; i>=1; i--) hr[b][i]=(hr[b][i+1]*base[b]+a[i])%mod[b];
	}
	for(int k=1; k<=n; k++){
	// cerr<<hl[0][1]<<' ';
	// cerr<<hl[0][2]<<' ';
		// cerr<<_ghl(0, 1, 1)<<'\n';
		// cerr<<_ghl(0, 2, 2)<<'\n';
	// for(int k=1; k<=1; k++){
		set <pair <ll, ll>> s;
		for(int i=1; i+k-1<=n; i+=k){
			int j=i+k-1;
			// cerr<<i<<' '<<j<<'\n';
			auto res=ghl(i, j);
			// cerr<<res.first<<' '<<res.second<<'\n';
			if(s.find(res)!=s.end()) continue;
			// cerr<<res.first<<' '<<res.second<<'\n';
			res=ghr(i, j);
			if(s.find(res)!=s.end()) continue;
			s.insert(res);
		}
		if(s.size()>ans){
			ans=s.size();
			bestk.clear();
			bestk.push_back(k);
		}
		else if(s.size()==ans) bestk.push_back(k);
	}
	cout<<ans<<' '<<bestk.size()<<'\n';
	for(auto &x: bestk) cout<<x<<' ';
	
}	