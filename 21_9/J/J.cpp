#include <bits/stdc++.h>
using namespace std;
long long n;
double m;
double f;
double deri(double n, double m, double x){
	return (-x*x*f-m+x*f*n*2)/(n-x)/(n-x);
}
double expt(double d, double n, double m){
	// cerr<<m<<' '<<d*d*f<<' '<<n-d<<'\n';
	return (m-d*d*f)/(n-d);
}
long long maximize(){
	///==(m-d^2*f)/(n-d)
	double low=0, high=(min(double(n-1), sqrt(m)/f));
	for(int i=1; i<=10000; i++){
		double llh=(low+low+high)/3;
		double lhh=(low+high+high)/3;
		
		auto resl=expt(llh, n, m);
		auto resr=expt(lhh, n, m);
		if(resl<resr){
			low=llh;
		}
		else high=lhh;
	}
	
	cerr<<expt(low, n, m)<<'\n';;
	return low;
}
double ans=0;
void check(long long x){
	if(x<0||x>n-1) return;
	ans=max(ans, expt(x, n, m));
}
int main(){
	cin>>n>>m;
	cin>>f;
	f=f*f;
	long long x=maximize();
	// cerr<<x<<'\n';
	for(int i=-10000; i<=10000; i++) check(x+i);
	check(0);
	check(n-1);
	// for(int i=-10; i<=10; i++) check(x+i);
	cout<<setprecision(16)<<fixed<<ans;
}