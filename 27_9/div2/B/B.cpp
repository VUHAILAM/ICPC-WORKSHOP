#include<bits/stdc++.h>
using namespace std;

// DATA TYPES
typedef long long ll;
#define double long double
//

// CONTAINERS
#define vec vector
#define pb push_back
#define ALL(x) begin(x), end(x)
#define SZ(x) (int)x.size()
#define mp make_pair
#define ii pair<int, int>
#define F first
#define S second
template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T, U> &L, const std::pair<T,U> &R) {
  return {L.first + R.first, L.second + R.second};
}
//

// LOOP
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define FORE(i, a, b) for(int i = (a); i <= (b); i++)
#define FORD(i, a, b) for(int i = (a); i >= (b); i--)
//

// BIT
#define bitcount(n) __builtin_popcountll(n)
//

// DEBUG
#define format(x) << #x << ": " << (x)
#define com << ", "
#define ndl << "\n"
#define debug1(x) cerr format(x) ndl;
#define debug2(x, y) cerr format(x) com format(y) ndl;
#define debug3(x, y, z) cerr format(x) com format(y) com format(z) ndl;
void debug_out() { cerr << "\n"; }
template <typename H, typename... T> 
void debug_out(H h, T... t) { cerr << " " << (h); debug_out(t...); }
#define DEBUG(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
// 

// CONSTANTS
const long long INF64 = 1e18;
const int INF32 = 1e9;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0L);
const double EPS = static_cast<double>(1e-9);
//

// NUMERICAL OPERATIONS
#define chmin(a, b) a = min(a, b)
#define chmax(a, b) a = max(a, b)

int norm(int a) {
  return ((a % MOD) + MOD) % MOD;
}

int mul(int a, int b) {
  return int(a * 1LL * b % MOD);
}

int binPow(int a, int k) {
  int ans = 1;
  for (; k > 0; k >>= 1) {
    if (k & 1) {
      ans = mul(ans, a);
    }
    a = mul(a, a);
  }
  return ans;
}

// If I need to find (x / a) % MOD, I need to use this function:
//    (x / a) % MOD = (x * inv(a)) % MOD
int inv(int a) {
  int b = binPow(a, MOD - 2);
  assert(mul(a, b) == 1);
  return b;
}
//

/*
 * Complexity: O(logN)
 */
template<typename num_t>
struct node_t {
    node_t *l, *r;
    int h, size, rev;
    num_t key, lz;
    node_t(num_t key, node_t* l = 0, node_t* r = 0, int h = rand()) : key(key), l(0), r(0), h(h) {
        size = (l ? l->size : 0) + 1 + (r ? r->size : 0);
        rev = lz = 0;
    }
};

template<typename num_t>
int size(node_t<num_t>* x) {
    return x ? x->size : 0;
}
template<typename num_t>
void pull(node_t<num_t>* x) {
    x->size = size(x->l) + 1 + size(x->r);
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

ll query(node_t<ll> *rt, int k) {
    // cerr << "rt: "; trace(rt);
    node_t<ll> *x, *y, *z;
    split(rt, x, y, z, k, k);
    // cerr << "rt: "; trace(rt);
    // cerr << "x: "; trace(x);
    // cerr << "y: "; trace(y);
    // cerr << "z: "; trace(z);
    ll res = y->key;
    rt = join(join(x, y), z);
    // cerr << "rt: "; trace(rt);
    return res;
}

char op[6];

void solve() {
  int n;
  scanf("%d", &n);
  int k;
  node_t<ll> *rt = 0;
  while (n--) {
      scanf("%s %d", op, &k);
      if (op[0] == '0') {
        //   trace(rt);
          k = size(rt) - k;
          printf("%lld\n", query(rt, k));
          continue;
      }
      if (op[0] == '-') {
          erase(rt, (ll)k);
      } else {
          insert(rt, (ll)k);
      }
  }
  // read the question correctly (is y a vowel?)
  // look out for SPECIAL CASES (n=1?) and overflow (ll vs int?)
}

int main() {
  //ios_base::sync_with_stdio(false); cin.tie();
  //auto beginProgram = chrono::steady_clock::now();
  //int t; scanf("%d", &t); while (t--) 
  {
    solve();
  }
  //auto endProgram = chrono::steady_clock::now();

  return 0;
}