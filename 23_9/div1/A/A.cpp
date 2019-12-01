#include <bits/stdc++.h>
using namespace std;
#define int long long
int n, q;
int a[200001];
class segment_tree{
public:
	using pointer=segment_tree*;
	int low, high, sum, mx, mi;
	int l, r, m;
	pointer left, right;
	segment_tree(int l, int r, int *a){
		this->l=l;
		this->r=r;
		m=(l+r)/2;
		sum=0;
		mx=-2e18;
		mi=2e18;
		if(l==r){
			low=high=a[l];
		}
		else{
			left=new segment_tree(l, m, a);
			right=new segment_tree(m+1, r, a);
			low=min(left->low, right->low);
			high=max(left->high, right->high);
		}
	}
	void down(){
		if(l==r) return;
		left->sum+=sum;
		left->high+=sum;
		left->low+=sum;
		left->mi+=sum;
		left->mx+=sum;
		
		right->sum+=sum;
		right->high+=sum;
		right->low+=sum;
		right->mi+=sum;
		right->mx+=sum;
		
		sum=0;
		
		left->mi=max(left->mi, mx);
		left->mx=max(left->mx, mx);
		right->mi=max(right->mi, mx);
		right->mx=max(right->mx, mx);
		
		left->low=max(left->low, mx);
		right->low=max(right->low, mx);
		left->high=max(left->high, mx);
		right->high=max(right->high, mx);
		
		mx=-2e18;
		
		left->mx=min(left->mx, mi);
		right->mx=min(right->mx, mi);
		left->mi=min(left->mi, mi);
		right->mi=min(right->mi, mi);
		left->low=min(left->low, mi);
		right->low=min(right->low, mi);
		left->high=min(left->high, mi);
		right->high=min(right->high, mi);
		mi=2e18;
	}
	void up(){
		low=min(left->low, right->low);
		high=max(left->high, right->high);
	}
	void update_max(int u, int v, int x){
		if(l>v||r<u) return;
		if(low>=x) return;
		if(u<=l&&v>=r){
			down();
			if(low==high){
				low=max(low, x);
				high=max(high, x);
				mx=x;
			}
			else{
				left->update_max(u, v, x);
				right->update_max(u, v, x);
				up();
			}
		}
		else{
			down();
			left->update_max(u, v, x);
			right->update_max(u, v, x);
			up();
		}
	}
	void update_min(int u, int v, int x){
		if(l>v||r<u) return;
		if(high<=x) return;
		if(u<=l&&v>=r){
			down();
			if(low==high){
				low=min(low, x);
				high=min(high, x);
				mi=x;
			}
			else{
				left->update_min(u, v, x);
				right->update_min(u, v, x);
				up();
			}
		}
		else{
			down();
			left->update_min(u, v, x);
			right->update_min(u, v, x);
			up();
		}
	}
	void update_sum(int u, int v, int x){
		if(l>v||r<u) return;
		if(u<=l&&v>=r){
			sum+=x;
			low+=x;
			high+=x;
			mx+=x;
			mi+=x;
		}
		else{
			down();
			left->update_sum(u, v, x);
			right->update_sum(u, v, x);
			up();
		}
	}
	int query_min(int u, int v){
		if(l>v||r<u) return 2e18;
		if(u<=l&&v>=r){
			return low;
		}
		else{
			down();
			return min(left->query_min(u, v), right->query_min(u, v));
		}
	}
	int query_max(int u, int v){
		if(l>v||r<u) return -2e18;
		if(u<=l&&v>=r){
			return high;
		}
		else{
			down();
			return max(left->query_max(u, v), right->query_max(u, v));
		}
	}
};
segment_tree::pointer tree;
signed main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	cin>>n>>q;
	for(int i=1; i<=n; i++) cin>>a[i];
	tree=new segment_tree(1, n, a);
	for(int i=1; i<=q; i++){
		int t, l, r, c;
		cin>>t>>l>>r;
		if(t==4){
			cout<<tree->query_min(l, r)<<' '<<tree->query_max(l, r)<<'\n';
		}
		else{
			cin>>c;
			if(t==1) tree->update_sum(l, r, c);
			else if(t==2) tree->update_min(l, r, c);
			else tree->update_max(l, r, c);
		}
	}
}	