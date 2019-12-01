#include <bits/stdc++.h>
using namespace std;

const int N = 300030;
const int mod = (998244353);
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int n;
int a[N];
int dp[N];
int cnt[N];
int sum[N];
// int cntmex[N];
// int current=-1;
// bool test(set<int> x){
	// int k=0;
	// while(x.find(k)!=x.end()) k++;
	// if(current==-1){
		// current=k;
		// return 1;
	// }
	// return current==k;
// }
// void brute(int u, set <int> now){
	// if(u==n+1){
		// if(now.empty())
		// dp[n]--;
	// }
	// else{
		// now.insert(a[u]);
		// brute(u+1, now);
		// int olc=current;
		// if(test(now)) brute(u+1, set <int>());
		// current=olc;
	// }
// }
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	int nTest; cin >> nTest;
	
	// nTest=1e5;
	while(nTest--) {
		cin >> n;
		// if(nTest%100==0) cerr<<nTest/100<<'\n';
		// n=rng()%15;
		for(int i = 0; i <= n + 5; ++i) {
			dp[i] = cnt[i] = sum[i] = 0;
		}
		
		for(int i = 1; i <= n; ++i) {
			cin >> a[i];
			++cnt[a[i]];
		}
		
		int mex = 0;
		while(cnt[mex]) ++mex;
	
		for(int i = 0; i <= n + 5; ++i) cnt[i] = 0;
		
		int need = 0;
		int l = 1, r = 0;
		
		while(need < mex) {
			++r;
			cnt[a[r]]++;
			if((a[r] < mex)&&(cnt[a[r]] == 1)) {
				++need;
			}
		}
	
	
		dp[0] = sum[0] = 1;
		dp[r] = 1;
		for(int i = 1; i <= r; ++i) sum[i] = sum[i - 1] + dp[i];
	
	
		for(int i = r + 1; i <= n; ++i) {
			if(a[i] < mex) ++cnt[a[i]];
	
			while((l < i) && ((cnt[a[l]] > 1) || (a[l] > mex))) {
				--cnt[a[l]];
				++l;
			}
	
			dp[i] = sum[l - 1];
			sum[i] = sum[i - 1] + dp[i];
			sum[i] %= mod;
			
			// cout << i << " " << l << " -> " << dp[i] << " " << sum[i] << endl;
		}
		// brute(1, set <int>());
		// if(dp[n]){
			// cout<<n<<'\n';
			// for(int i=1; i<=n; i++) cout<<a[i]<<" \n"[i==n];
			// exit(0);
		// }
		cout << dp[n] << '\n';
	}
	
}	