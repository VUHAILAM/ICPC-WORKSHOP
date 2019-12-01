#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	
	string test; cin >> test;
	
	cout << "....|.... buy ****|****" << endl;
	cout << "....|....     **..|...." << endl;
	cout << "---" << endl;
	
	for(int len = 1; len <= 15; ++len) {
		for(int start = 0; start < 16; ++start) {
			string eat(16, '.');
			for(int i = 0; i < len; ++i) eat[(start + i) % 16] = '*';
			
			string ans = eat; 
			ans[start] = '.';
			
			for(int i = 0; i < 4; ++i) cout << eat[i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << eat[4 + i];
			cout << " eat ";
			for(int i = 0; i < 4; ++i) cout << ans[i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << ans[4 + i];
			
			cout << endl;
			for(int i = 0; i < 4; ++i) cout << eat[8 + i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << eat[12 + i];
			cout << "     ";
			for(int i = 0; i < 4; ++i) cout << ans[8 + i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << ans[12 + i];
			cout << endl << "---" << endl;
		}
	}
	
	for(int len = 1; len <= 5; ++len){
		for(int start = 0; start < 16; ++start) {
			string eat(16, '.');
			for(int i = 0; i < len; ++i) eat[(start + i) % 16] = '*';
			string ans = eat;
			for(int i = 0; i < 10; ++i) ans[(start + i + len) % 16] = '*';
			
			
			for(int i = 0; i < 4; ++i) cout << eat[i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << eat[4 + i];
			cout << " buy ";
			for(int i = 0; i < 4; ++i) cout << ans[i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << ans[4 + i];
			
			cout << endl;
			for(int i = 0; i < 4; ++i) cout << eat[8 + i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << eat[12 + i];
			cout << "     ";
			for(int i = 0; i < 4; ++i) cout << ans[8 + i];
			cout << "|";
			for(int i = 0; i < 4; ++i) cout << ans[12 + i];
			cout << endl << "---" << endl;
		}
	}
	
}	