#include <bits/stdc++.h>
using namespace std;
using ll=long long;
class segment_tree{
public:
	int l, r, m;
	ll a, b;
	///get min (ai+bi)
	pair <ll, int> ans;
	int best;
	using pointer=segment_tree*;
	pointer left, right;
	void up(){
		if(left->b<right->b){
			b=left->b;
			best=left->best;
		}
		else{
			b=right->b;
			best=right->best;
		}
		ans=min(left->ans, right->ans);
	}
	void down(){
		left->a=min(left->a, a);
		left->ans=min(left->ans, make_pair(left->a+left->b, left->best));
		right->a=min(right->a, a);
		right->ans=min(right->ans, make_pair(right->a+right->b, right->best));
		a=1e18;
	}
	segment_tree(int l, int r, int *x){
		this->l=l;
		this->r=r;
		m=(l+r)/2;
		a=1e18;
		if(l==r){
			b=x[l];
			best=l;
			ans=make_pair(a+b, best);
		}
		else{
			left=new segment_tree(l, m, x);
			right=new segment_tree(m+1, r, x);
			up();
		}
	}
	void update(int u, int v, ll x){
		// cout<<l<<' '<<r<<' '<<a<<'\n';
		
		if(l>v||r<u) return;
		// cerr<<l<<' '<<r<<' '<<u<<' '<<v<<' '<<x<<'\n';
		if(u<=l&&v>=r){
			if(l!=r) down();
			a=min(a, x);
			ans=min(ans, make_pair(a+b, best));
			if(l!=r){
				ans=min(ans, left->ans);
				ans=min(ans, right->ans);
			} 
		}
		else{
			down();
			left->update(u, v, x);
			right->update(u, v, x);
			// cout << l << " " << r << " " << a << " " << b << " " << ans.first << endl;
			up();
		}
		// cout << l << " " << r << " " << a << " " << b << " " << ans.first << endl;
	}
	void erase_min(int x){
		if(l==r){
			b=1e18;
			a=1e18;
			ans=make_pair(a+b, best);
		}
		else{
			down();
			if(m>=x) left->erase_min(x);
			else right->erase_min(x);
			up();
		}
	}
};
int x[300001];
int n;
segment_tree:: pointer treel, treer;
void solve(){
	cin>>n;
	// cerr<<"OK\n";
	for(int i=1; i<=n; i++) cin>>x[i];
	treer=new segment_tree(1, n, x);
	for(int i=1; i<=n; i++) x[i]=-x[i];
	treel=new segment_tree(1, n, x);
	treel->update(1, 1, -x[1]);
	for(int i=1; i<=n; i++) x[i]=-x[i];
	// cerr<<"OK\n";
	ll ans=0;
	for(int i=1; i<=n; i++){
		// cerr<<"______________________________________\n";
		// cerr<<i<<'\n';
		int best;
		if(treer->ans<treel->ans){
			// cerr<<"RIGHT\n";
			ans+=treer->ans.first;
			best=treer->ans.second;
		}
		else{
			// cerr<<"LEFT\n";
			ans+=treel->ans.first;
			best=treel->ans.second;
		}
		// cerr<<best<<'\n';

		// cerr<<ans<<'\n';
		// cerr<<'\n';
		treel->erase_min(best);
		treer->erase_min(best);
		// cerr<<best<<'\n';
		treer->update(best, n, -x[best]);
		// cout << "------" << endl;
		treel->update(1, best, x[best]);
	}
	cout<<ans<<'\n';
}
int main(){
	try{
		ios_base::sync_with_stdio(false);
		cin.tie(NULL); cout.tie(NULL);
		int t;
		cin>>t;
		while(t--) solve();
	}
	catch(exception &e){
		cerr<<e.what()<<'\n';
	}
}