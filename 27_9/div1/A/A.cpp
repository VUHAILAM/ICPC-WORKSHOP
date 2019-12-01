#include <bits/stdc++.h>
#define x0 Aria
#define y0 aRia
#define x1 arIa
#define y1 ariA
using namespace std;
using ll=long long;
const ll base=1000000007;
int n;
ll x0[50001];
ll y0[50001];
ll x1[50001];
ll y1[50001];
ll f[50001];
class segment_tree{
public:
  using pointer=segment_tree*;
  int l, r, m, sz;
  ll a, b, lazya, lazyb;
  pointer left, right;
  segment_tree(int l, int r, vector<int> &v){
    this->l=l;
    this->r=r;
    m=(l+r)/2;
    a=lazya=0;
    b=lazyb=0;
    if(l==r){
      sz=v[l];
      left=right=nullptr;
    }
    else{
      left=new segment_tree(l, m, v);
      right=new segment_tree(m+1, r, v);
      sz=left->sz+right->sz;
    }
    //cerr<<l<<' '<<r<<' '<<sz<<'\n';
  }
  ~segment_tree(){
    if(left!=nullptr){
      delete left;
      delete right;
    }
  }
  void down(){
    if(lazya){
      left->a=(left->a+lazya*left->sz)%base;
      right->a=(right->a+lazya*right->sz)%base;
      left->lazya+=lazya;
      right->lazya+=lazya;
      while(left->lazya>=base) left->lazya-=base;
      while(right->lazya>=base) right->lazya-=base;
      lazya=0;
    }
    if(lazyb){
      left->b=(left->b+lazyb*left->sz)%base;
      right->b=(right->b+lazyb*right->sz)%base;
      left->lazyb+=lazyb;
      right->lazyb+=lazyb;
      while(left->lazyb>=base) left->lazyb-=base;
      while(right->lazyb>=base) right->lazyb-=base;
      lazyb=0;
    }
  }
  void update(int u, int v, ll x, ll y){
    if(l>v||r<u) return;
    if(u<=l&&v>=r){
      a+=x*sz;
      a%=base;
      lazya+=x;
      lazya%=base;
      b+=y*sz;
      b%=base;
      lazyb+=y;
      lazyb%=base;
    }
    else{
      down();
      left->update(u, v, x, y);
      right->update(u, v, x, y);
      a=left->a+right->a;
      while(a>=base) a-=base;
      b=left->b+right->b;
      while(b>=base) b-=base;
    }
  }
  ll geta(int u, int v){
    if(l>v||r<u) return 0;
    else if(u<=l&&v>=r) return a;
    else{
      down();
      ll res=left->geta(u, v)+right->geta(u, v);
      while(res>=base) res-=base;
      return res;
    }
  }
  ll getb(int u, int v){
    if(l>v||r<u) return 0;
    else if(u<=l&&v>=r) return b;
    else{
      down();
      ll res=left->getb(u, v)+right->getb(u, v);
      while(res>=base) res-=base;
      return res;
    }
  }
};
segment_tree::pointer tree;
namespace solver{
  vector <int> py;
  vector <int> px;
  vector <unsigned short> insS;
  vector <unsigned short> insE;
  vector <unsigned short> queS;
  vector <unsigned short> queE;
  int bs(int y){
    return lower_bound(py.begin(), py.end(), y)-py.begin();
  }
  void solve(int l, int m, int r){
    if(tree!=nullptr){
      delete tree;
    }
    px.clear();
    py.clear();
    for(int i=l; i<=r; i++){
      px.push_back(x0[i]);
      px.push_back(x1[i]);
      px.push_back(x0[i]-1);
      px.push_back(x1[i]-1);
    }
    for(int i=l; i<=r; i++){
      py.push_back(y0[i]);
      py.push_back(y1[i]);
      py.push_back(y0[i]-1);
      py.push_back(y1[i]-1);
    }
    sort(py.begin(), py.end());
    py.erase(unique(py.begin(), py.end()), py.end());
    sort(px.begin(), px.end());
    px.erase(unique(px.begin(), px.end()), px.end());
    for(int i=py.size()-1; i>=1; i--) py[i]-=py[i-1];
    tree=new segment_tree(1, py.size()-1, py);
    for(int i=1; i<py.size(); i++) py[i]+=py[i-1];
    insS.clear();
    queS.clear();
    for(int i=l; i<=m; i++) insS.push_back(i);
    for(int i=m+1; i<=r; i++) queS.push_back(i);
    insE=insS;
    queE=queS;
    sort(insS.begin(), insS.end(), [](int a, int b){
      return x0[a]>x0[b];
    });
    sort(queS.begin(), queS.end(), [](int a, int b){
      return x0[a]>x0[b];
    });
    sort(insE.begin(), insE.end(), [](int a, int b){
      return x1[a]>x1[b];
    });
    sort(queE.begin(), queE.end(), [](int a, int b){
      return x1[a]>x1[b];
    });
    for(int x: px){
      while(!insS.empty()){
        int i=insS.back();
        if(x0[i]==x){
          int low=bs(y0[i]);
          int high=bs(y1[i]);
          tree->update(low, high, f[i], base-(f[i]*(x-1))%base);
          insS.pop_back();
        }
        else break;
      }
      while(!queS.empty()){
        int i=queS.back();
        if(x0[i]-1==x){
          int low=bs(y0[i]);
          int high=bs(y1[i]);
          f[i]=(f[i]-tree->geta(low, high)*x-tree->getb(low, high))%base;
          if(f[i]<0) f[i]+=base;
          queS.pop_back();
        }
        else break;
      }
      while(!queE.empty()){
        int i=queE.back();
        if(x1[i]==x){
          int low=bs(y0[i]);
          int high=bs(y1[i]);
          f[i]=(f[i]+tree->geta(low, high)*x+tree->getb(low, high))%base;
          queE.pop_back();
        }
        else break;
      }
      while(!insE.empty()){
        int i=insE.back();
        if(x1[i]==x){
          int low=bs(y0[i]);
          int high=bs(y1[i]);
          tree->update(low, high, base-f[i], (f[i]*x)%base);
          insE.pop_back();
        }
        else break;
      }
    }
  }
}
void solve(int l, int r){
  if(l==r){
    f[l]=(f[l]+(x1[l]-x0[l]+1)*(y1[l]-y0[l]+1))%base;
    return;
  }
  int m=(l+r)/2;
  solve(l, m);
  solver::solve(l, m, r);
  solve(m+1, r);
}
ll g[101];
void brute(){
  for(int i=1; i<=n; i++){
    g[i]=((y1[i]-y0[i]+1)*(x1[i]-x0[i]+1))%base;
    for(int j=1; j<i; j++){
      int lx=max(x0[i], x0[j]);
      int hx=min(x1[i], x1[j]);
      if(lx>hx) continue;
      int ly=max(y0[i], y0[j]);
      int hy=min(y1[i], y1[j]);
      if(ly>hy) continue;
      g[i]=(g[i]+g[j]*(hx-lx+1)*(hy-ly+1))%base;
    }
  }
}
ll ans=0;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  cin>>n;
  //n=rng()%20+1;
  for(int i=1; i<=n; i++){
    cin>>x0[i]>>y0[i]>>x1[i]>>y1[i];
    /*x0[i]=rng()%10000+1;
    x1[i]=rng()%10000+1;
    y0[i]=rng()%10000+1;
    y1[i]=rng()%10000+1;
    if(x0[i]>x1[i]) swap(x0[i], x1[i]);
    if(y0[i]>y1[i]) swap(y0[i], y1[i]);*/
  }
  solve(1, n);
  for(int i=1; i<=n; i++){
    ans=(ans+f[i]*((x1[i]-x0[i]+1)*(y1[i]-y0[i]+1)%base))%base;
  }
  ans=(ans+base)%base;
  cout<<ans<<'\n';
  return 0;

}
