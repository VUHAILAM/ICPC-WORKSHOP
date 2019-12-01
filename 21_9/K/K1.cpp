#include <bits/stdc++.h>
#define FOR(i, u, v) for (int i = u; i <= v; i++)
#define pii pair<int, int>
#define mp make_pair
#define F first
#define S second
#define MM 700000
#define PB push_back
#define N 10005
#define maxc 1000000000
#define REP(i,n) for(int i = 0; i < (n); ++i)

using namespace std;

template<class Flow=int, class Cost=int>
struct MinCostFlow {
    const Flow INF_FLOW = 1000111000;
    const Cost INF_COST = 1000111000111000LL;

    int n, t, S, T;
    Flow totalFlow;
    Cost totalCost;
    vector<int> last, visited;
    vector<Cost> dis;
    struct Edge {
        int to;
        Flow cap;
        Cost cost;
        int next;
        Edge(int to, Flow cap, Cost cost, int next) :
                to(to), cap(cap), cost(cost), next(next) {}
    };
    vector<Edge> edges;

    MinCostFlow(int n) : n(n), t(0), totalFlow(0), totalCost(0), last(n, -1), visited(n, 0), dis(n, 0) {
        edges.clear();
    }

    int addEdge(int from, int to, Flow cap, Cost cost) {
        edges.push_back(Edge(to, cap, cost, last[from]));
        last[from] = t++;
        edges.push_back(Edge(from, 0, -cost, last[to]));
        last[to] = t++;
        return t - 2;
    }

    pair<Flow, Cost> minCostFlow(int _S, int _T) {
        S = _S; T = _T;
        SPFA();
        while (1) {
            while (1) {
                REP(i,n) visited[i] = 0;
                if (!findFlow(S, INF_FLOW)) break;
            }
            if (!modifyLabel()) break;
        }
        return make_pair(totalFlow, totalCost);
    }

private:
    void SPFA() {
        REP(i,n) dis[i] = INF_COST;
        priority_queue< pair<Cost,int> > Q;
        Q.push(make_pair(dis[S]=0, S));
        while (!Q.empty()) {
            int x = Q.top().second;
            Cost d = -Q.top().first;
            Q.pop();
            // For double: dis[x] > d + EPS
            if (dis[x] != d) continue;
            for(int it = last[x]; it >= 0; it = edges[it].next)
                if (edges[it].cap > 0 && dis[edges[it].to] > d + edges[it].cost)
                    Q.push(make_pair(-(dis[edges[it].to] = d + edges[it].cost), edges[it].to));
        }
        Cost disT = dis[T]; REP(i,n) dis[i] = disT - dis[i];
    }

    Flow findFlow(int x, Flow flow) {
        if (x == T) {
            totalCost += dis[S] * flow;
            totalFlow += flow;
            return flow;
        }
        visited[x] = 1;
        Flow now = flow;
        for(int it = last[x]; it >= 0; it = edges[it].next)
            // For double: fabs(dis[edges[it].to] + edges[it].cost - dis[x]) < EPS
            if (edges[it].cap && !visited[edges[it].to] && dis[edges[it].to] + edges[it].cost == dis[x]) {
                Flow tmp = findFlow(edges[it].to, min(now, edges[it].cap));
                edges[it].cap -= tmp;
                edges[it ^ 1].cap += tmp;
                now -= tmp;
                if (!now) break;
            }
        return flow - now;
    }

    bool modifyLabel() {
        Cost d = INF_COST;
        REP(i,n) if (visited[i])
            for(int it = last[i]; it >= 0; it = edges[it].next)
                if (edges[it].cap && !visited[edges[it].to])
                    d = min(d, dis[edges[it].to] + edges[it].cost - dis[i]);

        // For double: if (d > INF_COST / 10)     INF_COST = 1e20
        if (d == INF_COST) return false;
        REP(i,n) if (visited[i])
            dis[i] += d;
        return true;
    }
};

int n; 
int s, t;
int cntidx;
int idx[1000][1000];
MinCostFlow <int, long long > mf(N);

void build(int l, int r) {
	if(l == r) {
		idx[l][r] = r;
		return;
	}
	idx[l][r] = ++cntidx;
	int mid = (l + r) >> 1;
	build(l, mid);
	build(mid + 1, r);
	
	mf.addEdge(idx[l][r], idx[l][mid], n, 0);
	mf.addEdge(idx[l][r], idx[mid + 1][r], n, 0);
}

void add(int l, int r, int x, int y, int v, int w){
	if(l > y || r < x) return;
	if(l >= x && r <= y) {
		mf.addEdge(v, idx[l][r], n, w);
		return;
	}
	int mid = (l + r) >> 1;
	add(l, mid, x, y, v, w);
	add(mid + 1, r, x, y, v, w);
}

int main() {
	cin >> n;
	
	cntidx = n;
	build(1, n);
	int s = ++cntidx, t = ++cntidx;
	
	for(int i = 1; i <= n; ++i) {		
		if(i > 1) mf.addEdge(i, i - 1, n, 2);
		if(i < n) mf.addEdge(i, i + 1, n, 2);
		mf.addEdge(i, t, 1, 0);
	}
	
	for(int i = 1; i <= n; ++i) {
		int x, y; cin >> x >> y;
		if(x > y) swap(x, y);
		add(1, n, x, y, ++cntidx, y - x);
		mf.addEdge(s, cntidx, 1, 0);
	}
	
	cout << mf.minCostFlow(s, t).second << endl;
	
	return 0;
}