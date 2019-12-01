#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const ll base=1000000000;
ll C[14][14];
int id[14][14];
vector <pair <int, int>> v;
const int sz=106;
using matrix=ll[sz][sz];
matrix core;
matrix start;
matrix res;
matrix ans;
void multi(const matrix &A, const matrix &B, matrix &C){
	for(int i=0; i<sz; i++){
		for(int j=0; j<sz; j++){
			C[i][j]=0;
			for(int k=0; k<sz; k++){
				C[i][j]=(C[i][j]+A[i][k]*B[k][j])%base;
			}
		}
	}
}
void power(const matrix &A, uint64_t x, matrix &res){
	if(x==0){
		for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) res[i][j]=i==j;
		return;
	}
	matrix temp;
	for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) res[i][j]=A[i][j];
	for(int i=__lg(x)-1; i>=0; i--){
		multi(res, res, temp);
		if((x>>i)&1){
			multi(temp, A, res);
		}
		else{
			for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) res[i][j]=temp[i][j];
		}
	}
}
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	memset(id, -1, sizeof id);
	C[0][0]=1;
	const int MAX=13;
	for(int i=1; i<=MAX; i++){
		C[i][0]=C[i][i]=1;
		for(int j=1; j<i; j++) C[i][j]=(C[i-1][j]+C[i-1][j-1])%base;
	}
	for(int i=0; i<=MAX; i++){
		for(int j=0; j<=i; j++){
			id[j][i-j]=v.size();
			v.push_back(make_pair(j, i-j));
		}
	}
	// cerr<<"OK\n";
	// cerr<<v.size()<<'\n';
	uint64_t n, k;
	cin>>n>>k;
	for(int i=0; i<=MAX; i++){
		for(int j=0; j<=MAX; j++){
			if(id[i][j]>=0){
				//calculate f[u]^i*f[u-1]^j
				//=(f[u-1]+f[u-2]+1)^i*f[u-1]^j
				//=f[u-1]^x*f[u-2]^y*1^(i-x-y)*f[u-1]^j
				for(int x=0; x<=MAX; x++){
					for(int y=0; y<=MAX; y++){
						if(x+y>i) break;
						core[id[x+j][y]][id[i][j]]=(C[i][x+y]*C[x+y][x])%base;
						// cerr<<i<<' '<<j<<" = "<<(C[i][x+y]*C[x+y][x])%base<<"X "<<x+j<<' '<<y<<'\n';
						if(i==k&&j==0) core[id[x+j][y]][sz-1]=core[id[x+j][y]][id[i][j]];
					}
				}
			}
		}
	}
	core[sz-1][sz-1]=1;
	for(int j=0; j<sz; j++) start[0][j]=1;
	start[0][sz-1]=2;
	power(core, n-1, res);
	multi(start, res, ans);
	// for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) cerr<<start[i][j]<<" \n"[j+1==sz];
	// cerr<<"_________________________________________\n";
	// for(int i=0; i<sz; i++) for(int j=0; j<sz; j++) cerr<<ans[i][j]<<" \n"[j+1==sz];
	cout<<setw(9)<<setfill('0')<<ans[0][sz-1]<<'\n';
}	