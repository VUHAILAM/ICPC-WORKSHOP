#include <bits/stdc++.h>

using namespace std;

const int N = 1000100;

int n;
long long f[N];
long long prefix[N];
long long bit[2][N];

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);


  int n, a, b; cin >> n >> a >> b;
  vector < long long > vals = {0, (long long)1e18};

  for(int i = 1; i <= n; ++i) {
    cin >> prefix[i];
    prefix[i] += prefix[i - 1];
    long long S = a + b - prefix[i - 1];
    vals.push_back(S + prefix[i - 1] + 1);
  }

  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());

  f[n + 1] = 1e18 + 5;
  for(int i = 0; i < N; ++i) {
    bit[0][i] = -f[n + 1];
    bit[1][i] = f[n + 1];
  }

  int pos = lower_bound(vals.begin(), vals.end(), prefix[n] + f[n + 1]) - vals.begin() + 1;
  for(int x = pos; x < N; x += x & -x) bit[0][x] = max(bit[0][x], f[n + 1]);
  for(int x = pos; x > 0; x -= x & -x) bit[1][x] = min(bit[1][x], prefix[n]);
  for(int i = n; i >= 1; --i) {
    f[i] = 1e18 + 5;
    long long S = a + b - prefix[i - 1];
    int idx = lower_bound(vals.begin(), vals.end(), S + prefix[i - 1] + 1) - vals.begin() + 1;
    for(int x = idx; x > 0; x -= x & -x) f[i] = min(f[i], S - bit[0][x] + 1);
    for(int x = idx; x < N; x += x & -x) f[i] = min(f[i], bit[1][x] - prefix[i - 1]);
    int pos = upper_bound(vals.begin(), vals.end(), prefix[i - 1] + f[i]) - vals.begin() + 1;
    for(int x = pos; x < N; x += x & -x) bit[0][x] = max(bit[0][x], f[i]);
    for(int x = pos - 1; x > 0; x -= x & -x) bit[1][x] = min(bit[1][x], prefix[i - 1]);
  }

  if(f[1] > a) cout << "BOB";
  else cout << "ALICE";

  return 0;
}
