#include <bits/stdc++.h>
using namespace std;

int n; 

class FastFourierTransform{
	struct ComplexNumber{
		double x, y;
		ComplexNumber() { x = 0, y = 0; } ;
		ComplexNumber(double x, double y) : x(x), y(y) {}
		
		ComplexNumber operator +(const ComplexNumber &rhs) const{
			return ComplexNumber(x + rhs.x, y + rhs.y);
		}
		
		ComplexNumber operator -(const ComplexNumber &rhs) const{
			return ComplexNumber(x - rhs.x, y - rhs.y);
		}
		
		ComplexNumber operator *(const ComplexNumber &rhs) const{
			return ComplexNumber(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
		}
	};
	
	static const int MAXF = 18;
	static const int N = (1 << MAXF);
	
	int revbit[N];
	ComplexNumber fpow[N], a[N], b[N];
	
	void permute(ComplexNumber *a) {
		for(int i = 0; i < N; ++i) {
			if(i < revbit[i]) swap(a[i], a[revbit[i]]);
		}
	}
	
	void dft(ComplexNumber * a, bool invert = false){ 
		permute(a);
		for(int len = 2; len <= N; len <<= 1) {
			int len2 = len >> 1;
			
			fpow[0] = ComplexNumber(1, 0);
			ComplexNumber alpha = ComplexNumber(cos(2.0 * acos(-1) / len * (invert ? -1 : 1)), sin(2.0 * acos(-1) / len * (invert ? -1 : 1)));
		
			for(int j = 1; j < len2; ++j) fpow[j] = fpow[j - 1] * alpha;
	
			for(int i = 0; i < N; i += len) {
				for(int j = 0; j < len2; ++j) {
					ComplexNumber tmp = a[i + j + len2] * fpow[j];
					a[i + j + len2] = a[i + j] - tmp;
					a[i + j] = a[i + j] + tmp;
				}
			}
		}
		
		if(invert) for(int i = 0; i < N; ++i) {
			a[i].x /= N;
			a[i].y /= N;
		}
	}
	
public:
	FastFourierTransform() {
		for(int i = 0; i < N; ++i) revbit[i] = (revbit[i >> 1] >> 1) + (i & 1 ? (1 << MAXF - 1) : 0);
	}
	
	vector < long long > fft(vector < long long > &x, vector < long long > &y) {
		for(int i = 0; i < N; ++i) {
			a[i] = (i < x.size() ? ComplexNumber(x[i], 0) : ComplexNumber(0, 0));
			b[i] = (i < y.size() ? ComplexNumber(y[i], 0) : ComplexNumber(0, 0));
		}
		
		dft(a, false);		
		dft(b, false);
		
		for(int i = 0; i < N; ++i) a[i] = a[i] * b[i];
		dft(a, true);
		
		vector < long long > ret(N);
		for(int i = 0; i < N; ++i) {
			ret[i] = (long long) (a[i].x + 0.5);
		}
		return ret;
	}
}fft;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	

	int p; cin >> p;
	
	int low = 0, high = p - 1, ans = -1;
	while(low <= high) {
		int mid = (low + high >> 1);
		
		vector < long long > a(p, 0), b(p, 0), c;
		
		for(int i = 0; i < p; ++i) {
			b[(1LL * i * i) % p]++;
		}
		
		for(int i = 0; i <= mid; ++i) {
			a[(1LL * i * i) % p]++;
		}
		
		c = fft.fft(a, b);
		c.resize(p + p);	
		bool flag = false;
		
		for(int x = p; x < p + p; ++x) c[x - p] += c[x];
		
		for(int x = 0; x < p; ++x) {
			if(c[x] == 0) flag = true;
		}
		
		if(flag) {
			low = mid + 1;
		}
		else {
			ans = mid;
			high = mid - 1;
		}
	}
	
	cout << ans;
}	