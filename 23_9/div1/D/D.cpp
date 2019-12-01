#include <bits/stdc++.h>
using namespace std;
int n;
vector <int> a[1000001];
int done[5000001];
vector <int> ans;
// int t;
// pair <int, vector <int>> temp;
// void make(int low, int high, int pos){
	// if(low+1==high) return;
	// t++;
	// temp.clear();
	// for(int i=low; i<high; i++){
		// if(done[a[ans[i]][pos]]!=t){
			// done[a[ans[i]][pos]]=t;
			// temp.push_back(make_pair(a[ans[i]][pos], vector <int>()));
		// }
	// }
	// sort(temp.begin(), temp.end());
// }
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>n;
	for(int i=1, sz; i<=n; i++){
		cin>>sz;
		a[i].resize(sz);
		for(auto &x: a[i]) cin>>x;
		ans.push_back(i);
	}
	// for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) cerr<<(a[i]<a[j])<<" \n"[j==n];
	// make(0, n, 0);
	stable_sort(ans.begin(), ans.end(), [](int x, int y){
		return a[x]<a[y];
	});
	for(int id: ans) cout<<id<<'\n';
}	