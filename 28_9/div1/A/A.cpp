#include <bits/stdc++.h>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);

  int n, numQ;
  cin >> n >> numQ;

  int x; int cnt = 0;
  for (int i = 1; i <= n; i++) cin >> x;
  for (int i = 1; i <= n; i++) {
    cin >> x;
    if (x == 1) cnt = 1;
  }
  while (numQ--) {
    cin >> x;
    if (x <= 0) cout <<"NO"<<'\n';
    else if (cnt == 1) cout <<"YES"<<'\n';
    else {
      if (x % 2 == 0) cout <<"YES"<<'\n';
      else cout <<"NO"<<'\n';
    }
  }
  return 0;
}