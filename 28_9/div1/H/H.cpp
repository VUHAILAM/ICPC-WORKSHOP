#include <bits/stdc++.h>

using namespace std;
double p[16];
double stop[16][16];
double visit[16][16];
double conti[16][16];
double h[16][16];
double f[16][17][17];///chance that j people stop at i and k continue
int m, n;
const double one=1;
int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  while(cin>>m>>n){
    double ans=0;
    for(int i=0; i<m; i++) cin>>p[i];
    for(int i=0; i<m; i++) for(int j=0; j<n; j++) cin>>h[i][j];
    for(int i=0; i<m; i++){
      visit[i][0]=1;
      for(int j=0; j<n-1; j++){
        visit[i][j+1]=visit[i][j]*p[i];
      //  stop[i][j]=visit[i][j]-visit[i][j+1];
      }
    //  stop[i][n-1]=visit[i][n-1];
    //  for(int j=0; j<n; j++) conti[i][j]=one-stop[i][j];
    }
    for(int a=0; a<m; a++){
      for(int i=0; i<n; i++) for(int j=0; j<=m; j++) for(int k=0; k<=m; k++) f[i][j][k]=0;
      for(int j=0; j<n; j++) f[j][0][0]=1;
      for(int i=0; i<m; i++) if(i!=a) for(int j=0; j<n; j++){
        for(int x=m; x>=0; x--){
          for(int y=x; y>=0; y--){
            f[j][x][y]=f[j][x][y]*(one-visit[i][j]);
            if(x&&y) f[j][x][y]+=f[j][x-1][y-1]*visit[i][j]*p[i];
            if(x) f[j][x][y]+=f[j][x-1][y]*visit[i][j]*(one-p[i]);
          }
        }
      }
      for(int j=0; j<n; j++){
        //cerr<<j<<'\n';
        double sum=0;
      //  for(int x=0; x<=m; x++) for(int y=0; y<=m; y++) cerr<<setw(16)<<f[j][x][y]<<" \n"[y==m];
        for(int x=0; x<=m; x++) for(int y=0; y<=m; y++) sum+=f[j][x][y];
        //cerr<<sum<<'\n';
      //  cerr<<"_________________________________________\n";

      }
      ans+=h[a][0];
      for(int i=1; i<n; i++){
        ans+=h[a][i]*visit[a][i];
        for(int j=0; j<=m; j++) for(int k=0; k<=j; k++){
          ans+=(h[a][i]*visit[a][i]*f[i-1][j][k]*(k+1))/(j+1);
        }
      }
    }
    cout<<setprecision(16)<<fixed<<ans<<'\n';
  }
  return 0;
}
