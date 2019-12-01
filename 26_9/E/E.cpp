#include <bits/stdc++.h>
using namespace std;

const int M = 300040;
const int N = 300040;
const long long Worst = (1LL << 60);

struct LichaoTree{
	private:
		struct TLine{
			long long x, y;
			TLine(long long u = Worst, long long v = Worst) {
				x = u;
				y = v;
			}
			long long f(long long p) {
				if(x == Worst) return Worst;
				return x * p + y;
			}
		};

		struct TNode{
			TNode *L;
			TNode *R;
			TLine val;

			TNode() {
				L = R = NULL;
				val = TLine();
			}
		};

		TNode *root;

		void add(TNode *&p, int l, int r, TLine nw) {
			if(!p) p = new TNode();
			if(p -> val.f(l) < nw.f(l) && p -> val.f(r) < nw.f(r)) return;
			if(p -> val.f(l) > nw.f(l) && p -> val.f(r) > nw.f(r)) {
				p -> val = nw;
				return;
			}
			
			if(l==r) return;

			int m = (l + r) >> 1;
			if(p -> val.f(l) > nw.f(l)) swap(p -> val, nw);
			if(p -> val.f(m) < nw.f(m)) add(p -> R, m + 1, r, nw);
			else {
				swap(p -> val, nw);
				add(p -> L, l, m, nw);
			}
		}

		long long ask(TNode *p, int l, int r, long long x) {
			if(!p) return Worst;
			int m = (l + r) >> 1;
			if(x > m) return min(p -> val.f(x), ask(p -> R, m + 1, r, x));
			return min(p -> val.f(x), ask(p -> L, l, m, x));
		}

	public:
		LichaoTree() {
			root = new TNode();
		}

		void update(long long u, long long v) {
			add(root, 0, M, TLine(u, v));
		}

		long long query(long long u) {
			return ask(root, 0, M, u);
		}
};

int n;
int pos[N];
LichaoTree T[N << 2];

#define mid ((l + r) >> 1)

void build(int x, int l, int r) {
	T[x] = LichaoTree();
	if(l == r) {
		pos[r] = x;
		return;
	}
	build(x + x, l, mid);
	build(x + x + 1, mid + 1, r);
}

int find(int x, int l, int r, long long u, long long v) {
	if(-T[x].query(u) < v) return 1;
	if(l == r) return r + 1;
	if(-T[x + x + 1].query(u) >= v) return find(x + x + 1, mid + 1, r, u, v);
	return find(x + x, l, mid, u, v);
}

void addLine(int p, long long x, long long y) {
	p = pos[p];

	while(p) {
		T[p].update(x, y);
		p >>= 1;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int nTest; cin >> nTest;
	while(nTest--){
		cin >> n;
		build(1, 1, n);
		int risan = 0;
		for(int i = 1; i <= n; ++i) {
			long long a, b, x, y;
			cin >> a >> b >> x >> y;
			int ans = find(1, 1, n, x, y);
			risan = max(risan, ans);
			addLine(ans, -a, -b);
		}

		cout << risan << '\n';
	}

	return 0;
}