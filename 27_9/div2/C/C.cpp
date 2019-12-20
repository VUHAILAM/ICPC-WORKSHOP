#include<bits/stdc++.h>
using namespace std;

/* Treap
 * Complexity: O(logN)
 */
template<typename num_t>
struct node_t {
  node_t *l, *r;
  int h, size, rev;
  num_t key, lz;
  num_t minKey;
  node_t(num_t key, node_t* l = 0, node_t* r = 0, int h = rand()) : key(key), l(0), r(0), h(h) {
    size = (l ? l->size : 0) + 1 + (r ? r->size : 0);
    rev = lz = 0;
    minKey = key;
  }
};

template<typename num_t>
int minKey(node_t<num_t>* x) {
  return x ? x->minKey : INT_MAX;
}
template<typename num_t>
int size(node_t<num_t>* x) {
  return x ? x->size : 0;
}
template<typename num_t>
void pull(node_t<num_t>* x) {
  x->size = size(x->l) + 1 + size(x->r);
  x->minKey = min(min(minKey(x->l), minKey(x->r)), x->key);
}
template<typename num_t>
void push(node_t<num_t>* x) {
  node_t<num_t>* u = x->l;
  node_t<num_t>* v = x->r;
  if (x->rev) {
    if (u) swap(u->l, u->r), u->rev ^= 1;
    if (v) swap(v->l, v->r), v->rev ^= 1;
    x->rev = 0;
  }
  if (x->lz) {
    if (u) u->key += x->lz, u->lz += x->lz;
    if (v) v->key += x->lz, v->lz += x->lz;
    x->lz = 0;
  }
}
template<typename num_t>
node_t<num_t>* join(node_t<num_t>* x, node_t<num_t>* y) {
  if (!x) return y;
  if (!y) return x;
  if (x->h < y->h) {
    push(x);
    x->r = join(x->r, y);
    pull(x);
    return x;
  }
  push(y);
  y->l = join(x, y->l);
  pull(y);
  return y;
}
template<typename num_t>
void split(node_t<num_t>* x, node_t<num_t>*& l, node_t<num_t>*& r, int pos) {
  if (!x) {
    l = r = 0;
    return;
  }
  push(x);
  if (size(x->l) + 1 <= pos) {
    split(x->r, x->r, r, pos - size(x->l) - 1);
    pull(l = x);
  }
  else {
    split(x->l, l, x->l, pos);
    pull(r = x);
  }
}
template<typename num_t>
void split(node_t<num_t>* t, node_t<num_t>*& x, node_t<num_t>*& y, node_t<num_t>*& z, int l, int r) {
  split(t, x, y, l);
  split(y, y, z, r - l + 1);
}
template<typename num_t>
void reverse(node_t<num_t>*& x, int l, int r) {
  node_t<num_t> *y, *z;
  split(x, x, y, z, l, r);
  y->rev ^= 1;
  swap(y->l, y->r);
  x = join(x, join(y, z));
}
template<typename num_t>
void upd(node_t<num_t>*& x, int l, int r, num_t val) {
  node_t<num_t> *y, *z;
  split(x, x, y, z, l, r);
  y->lz += val;
  y->key += val;
  x = join(x, join(y, z));
}
template<typename num_t>
void split(node_t<num_t>* x, node_t<num_t>*& l, node_t<num_t>*& r, const function<bool(node_t<num_t>*)>& go_right) {
  if (!x) {
    l = r = 0;
    return;
  }
  push(x);
  if (go_right(x)) {
    split(x->r, x->r, r, go_right);
    pull(l = x);
  }
  else {
    split(x->l, l, x->l, go_right);
    pull(r = x);
  }
}
template<typename num_t>
void insert(node_t<num_t>*& x, num_t key) {
  node_t<num_t>* y;
  split<num_t>(x, x, y, [&] (node_t<num_t>* x) {
      return x->key < key;
    }
  );
  x = join(x, join(new node_t<num_t>(key), y));
}
template<typename num_t>
node_t<num_t>* erase(node_t<num_t>*& x, num_t key) {
  node_t<num_t> *l, *r, *res;
  split<num_t>(x, l, res, [&] (node_t<num_t>* x) {
      return x->key < key;
    }
  );
  split<num_t>(res, res, r, [&] (node_t<num_t>* x) {
      return x->key <= key;
    }
  );
  x = join(l, r);
  return res;
}
template<typename num_t>
void free(node_t<num_t>*& x) {
  if (!x) return;
  free(x->l);
  free(x->r);
  delete x;
  x = 0;
}
template<typename num_t>
int depth(node_t<num_t>* x) {
  if (!x) return 0;
  push(x);
  return 1 + max(depth(x->l), depth(x->r));
}
template<typename num_t>
void trace(node_t<num_t>* x, int isrt = 1) {
  if (!x) return;
  push(x);
  trace(x->l, 0);
  cerr << "(" << x->key << ") ";
  trace(x->r, 0);
  if (isrt) {
    cerr << "\n";
  }
}
template<typename num_t>
void insert(node_t<num_t>*& x, int pos, num_t key) {
  node_t<num_t> *a, *b;
  split(x, a, b, pos);
  //cerr << "a:\n"; trace(a);
  //cerr << "b:\n"; trace(b);
  x = join(join(a, new node_t<num_t>(key)), b);
}

node_t<int>* rt = 0;
char op[2];

void output(int L, int R) {
  //trace(rt);
  node_t<int> *a, *b, *c;
  split(rt, a, b, c, L, R);
  //cerr << "range: "; trace(b);
  printf("%d\n", minKey(b));
  rt = join(join(a, b), c);
  //trace(rt);
}

// look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
int main() {
  //auto beginProgram = chrono::steady_clock::now();
  srand(time(0));
  int n;
  scanf("%d", &n);
  int p, q;
  while (n--) {
    scanf("%s %d %d", op, &p, &q);
    if (op[0] == '+') {
      insert(rt, p, q); 
    } else {
      output(p - 1, q - 1);
    }
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}
