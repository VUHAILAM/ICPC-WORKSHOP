#include <bits/stdc++.h>

using namespace std;

const int mod = 1e9 + 7;

int fpow(int x, int y) {
  int ret = 1;
  while(y) {
    if(y & 1) ret = (1LL * ret * x) % mod;
    x = (1LL * x * x) % mod;
    y >>= 1;
  }
  return ret;
}

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  string s;
  cin >> s;

  long long w = 0;
  for(int i = 0; i < s.size(); ++i) {
    w = (w * 10 + s[i] - '0') % (mod - 1);
  }

  w -= 1;
  if(w < 0) w += mod - 1;

  cout << fpow(2, w) << endl;

  return 0;
}