#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define PB push_back
#define ll long long
#define N 2005
#define mod 1000000007

using namespace std;

void inline add(int &A, int B) {A += B; if (A >= mod) A -= mod;}
void inline sub(int &A, int B) {A -= B; if (A < 0) A += mod;}
int inline mul(int A, int B) {return (1ll*A*B) % mod;}

struct Segment {
  int l, r;
  vector<int> ally;
  Segment(int _l=0, int _r=0) : l(_l), r(_r) {
    ally.resize(0);
  }
};

int n, m, k;
pii a[N];

vector<Segment> allx;
int resY = 0;

set<int> s;

int getAns(int l, int r) {
  int sz = (r - l + 1);
  return ((1ll*sz*(sz+1))/2) % mod;
}
void Insert(int x) {
  auto it = s.lower_bound(x);
  if ((*it) == x) return;

  int R = (*it);
  it--;
  int L = (*it);

  sub(resY, getAns(L+1, R-1));
  add(resY, getAns(L+1, x-1));
  add(resY, getAns(x+1, R-1));

  s.insert(x);
}
int main() {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  //freopen("1.inp", "r", stdin);
  cin >> n >> m >> k;
  for (int i = 1; i <= k; i++) cin >> a[i].F >> a[i].S;
  sort(a+1, a+k+1);

  int preX = 0;
  FOR(i, 1, k) {
    if (a[i].F > preX) {
      if (a[i].F-1 >= preX+1)
        allx.PB(Segment(preX+1, a[i].F-1));
      allx.PB(Segment(a[i].F, a[i].F));
      preX = a[i].F;
    }
    allx[(int)allx.size()-1].ally.PB(a[i].S);
  }
  if (preX < n) allx.PB(Segment(preX+1, n));


  int res = mul(getAns(1, n), getAns(1, m));
  FOR(i, 0, (int)allx.size()-1) {
    s.clear();
    s.insert(0); s.insert(m+1);
    resY = getAns(1, m);
    //cout <<resY<<endl;
    FOR(j, i, (int)allx.size()-1) {
      for (auto yy : allx[j].ally)
        Insert(yy);

      int resX = mul(allx[i].r - allx[i].l + 1, allx[j].r - allx[j].l + 1);
      if (i == j) resX = getAns(allx[i].l, allx[i].r);

      sub(res, mul(resX, resY));

      //cout <<i<<' '<<j<<' '<<resX<<' '<<resY<<endl;
    }
  }
  cout <<res<<endl;
}