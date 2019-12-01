#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

int typ[N], par[N];
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int main(){
	int n; cin >> n;
	vector < pair < int, int > > a(n + 5);
	
	vector < int > tall, low;
	
	
	for(int i = 1; i <= n; ++i) {
		cin >> typ[i] >> par[i];
		if(typ[i] == 1) tall.push_back(i);
		else low.push_back(i);
	}
	
	
	for(int rd = 0; rd < 200; ++rd){
		// cerr<<rd<<'\n';
		shuffle(low.begin(), low.end(), rng);
		bool flag = false;
		for(int i = 0; i < n / 2; ++i) {
			if(tall[i] == par[low[i]] || low[i] == par[tall[i]]) {
				flag = true;
				break;
			}
		}
		if(flag == false) {
			for(int i = 0; i < n / 2; ++i) {
				cout << tall[i] << " ";
			}
			cout << endl;
			
			for(int i = 0; i < n / 2; ++i) {
				cout << low[i] << " ";
			}
			exit(0);
		}
	}
	cout << "impossible";
}
	