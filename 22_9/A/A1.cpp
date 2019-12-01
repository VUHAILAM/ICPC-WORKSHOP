#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
using ll=long long;
const ll base=1000000007;
ll power(ll x, ll y){
	if(y==0) return 1;
	ll t=power(x, y/2);
	t=(t*t)%base;
	if(y%2) t=(t*x)%base;
	return t;
}
ll inverse(ll x){
	return power(x, base-2);
}
class gauss{
public:
	class equation: public vector <ll>{
	public:
		equation operator - (equation x){
			equation res=*this;
			for(int i=0; i<size(); i++){
				res[i]=(res[i]+base-x[i])%base;
			}
			return res;
		}
		equation operator * (long long x){
			equation res=*this;
			for(int i=0; i<size(); i++){
				res[i]=(res[i]*x)%base;
			}
			return res;
		}
	};
	vector <equation> E;
	void clear(){
		E.clear();
	}
	vector <ll> solve(){
		// cerr<<"____________________________________\n";
		// cerr<<"____________________________________\n";
		// for(int i=0; i<E.size(); i++){
			// for(auto &x: E[i]) cerr<<x<<' ';
			// cerr<<'\n';
		// }
		// cerr<<"____________________________________\n";
		for(int i=0; i<E.size(); i++){
			for(int j=i; j<E.size(); j++) if(E[j][i]){
				swap(E[j], E[i]);
				break;
			}
			E[i]=E[i]*inverse(E[i][i]);
			for(int j=0; j<E.size(); j++) if(j!=i) E[j]=E[j]-(E[i]*E[j][i]);
			// cerr<<"____________________________________\n";
			// for(int i=0; i<E.size(); i++){
				// for(auto &x: E[i]) cerr<<x<<' ';
				// cerr<<'\n';
			// }
			// cerr<<"____________________________________\n";
		}
		// cerr<<"____________________________________\n";
		// cerr<<"____________________________________\n";
		vector <ll> ans;
		for(int i=0; i<E.size(); i++) ans.push_back(E[i].back());
		return ans;
	}
	void add_equation(ll x, ll a, int deg){
		ll t=1;
		equation e;
		e.clear();
		for(int i=0; i<=deg; i++){
			e.push_back(t);
			t=(t*x)%base;
		}
		e.push_back(a);
		E.push_back(e);
	}
} G;
pair <ll, ll> check;
bool solve(vector <pair <ll, ll>> f){
	G.clear();
	for(auto x: f) G.add_equation(x.first, x.second, f.size()-1);
	auto res=G.solve();
	ll h=0;
	for(auto x: res) h=(h+x)%base;
	return res.back()||(h!=check.second);
}
// int d[]={2, 1000000005, 8, 7, 7, 0, 0, 0, 9, 0, 10, 0, 0};
int d[]={1000000005, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
ll get(ll x){
	ll t=1;
	ll res=0;
	for(int i=0; i<12; i++){
		res=(res+t*d[i])%base;
		t=(t*x)%base;
	}
	return res;
}
pair <ll, ll> ask(ll x){
	cout<<"ask "<<x<<'\n';
	fflush(stdout);
	long long res;
	cin>>res;
	assert(res!=-1);
	// res=get(x);
	return make_pair(x, res);
}
void answer(int d){
	cout<<"degree "<<d<<'\n';
	fflush(stdout);
	exit(0);
}
int main(){
	// ios_base::sync_with_stdio(false);
	// cin.tie(NULL); cout.tie(NULL);
	vector <pair <ll, ll>> f;
	check=ask(1);
	// cerr<<check.second<<'\n';
	for(int i=0; i<=0; i++) f.push_back(ask(rng()%base));
	for(int i=0; i<=10; i++){
		f.push_back(ask(rng()%base));
		if(!solve(f)) answer(i);
	}
	// cerr<<"FAIL\n";
}