#include <bits/stdc++.h>

using namespace std;
int q;
class segment_tree{
public:
  using pointer=segment_tree*;
  int l, r, m, a;
  pointer left, right;
  segment_tree(int l, int r){
    this->l=l;
    this->r=r;
    m=(l+r)/2;
    a=0;
    if(l!=r){
      left=new segment_tree(l, m);
      right=new segment_tree(m+1, r);
    }
    else left=right=nullptr;
  }
  void update(int u, int x){
    if(l==r) a=x;
    else{
      if(m>=u) left->update(u, x);
      else right->update(u, x);
      a=max(left->a, right->a);
    }
  }
  int get(int u){
    if(l>u) return -1e9;
    if(r<=u) return a;
    return max(left->get(u), right->get(u));
  }
};
segment_tree::pointer tree;
class item{
public:
  using pointer=item*;
  int value;
  int pref;
  int pos;
  pointer next, prev;
  item(){
    value=pref=pos=0;
    next=prev=nullptr;
  }
  void update(){
    pos=prev->pos+1;
    pref=prev->pref+value;
    tree->update(pos, pref);
  }
};
item::pointer root;
item::pointer now;
int main(){
  ios_base::sync_with_stdio(false); cin.tie(NULL);
  root=new item();
  now=root;
  tree=new segment_tree(1, 1000000);
  cin >> q;
  while(q--){
    char c;
    cin>>c;
    if(c=='I'){
      item::pointer nx;
      nx=new item();
      nx->prev=now;
      nx->next=now->next;
      if(now->next!=nullptr) now->next->prev=nx;
      now->next=nx;
      now=nx;
      int x;
      cin>>x;
      now->value=x;
      now->update();
    }
    else if(c=='D'){
      if(now==root) continue;
      now->prev->next=now->next;
      if(now->next!=nullptr) now->next->prev=now->prev;
      now=now->prev;
    }
    else if(c=='L'){
      if(now==root) continue;
      now=now->prev;
    }
    else if(c=='R'){
      if(now->next==nullptr) continue;
      now=now->next;
      now->update();
    }
    else{
      int k;
      cin>>k;
      cout<<tree->get(k)<<'\n';
    }
  }

  return 0;
}