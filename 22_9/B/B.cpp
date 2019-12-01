#include <bits/stdc++.h>
using namespace std;
using ll=long long;
ll inputgame(){
	ll game=0;
	for(int i=0; i<8; i++) for(int j=0; j<8; j++){
		int x;
		cin>>x;
		if(x) game^=1LL<<(i*8+j);
	}
	return game;
}
void output(long long game){
	for(int i=0; i<8; i++) for(int j=0; j<8; j++){
		cout<<((game>>(i*8+j))&1)<<" \n"[j==7];
	}
	cout<<"---\n";
}
void mia(){
	int t;
	cin>>t;
	while(t--){
		ll game=inputgame();
		int x;
		cin>>x;
		x%=64;
		int now=0;
		for(int i=0; i<64; i++) if((game>>i)&1) now^=i;
		game^=1LL<<(now^x);
		output(game);
	}
}
void danila(){
	int t;
	cin>>t;
	while(t--){
		ll game=inputgame();
		int now=0;
		for(int i=0; i<64; i++) if((game>>i)&1) now^=i;
		if(now==0) now=64;
		cout<<now<<'\n';
		string ign;
		cin>>ign;
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	string test;
	cin>>test;
	if(test=="Mia") mia();
	else danila();
}	