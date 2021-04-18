#include <bits/stdc++.h>

using namespace std;

const int INF = int(2e9) + 2110;

const int N = 100005;

int f(int a, int b) {
	return (a + b); // ?
}

struct Node {	
	
	Node *l = 0, *r = 0;	
	
	int value = 0; // ?
	int mset = INF, madd = 0;
	int low, high;
	
	Node(int lo, int hi) : low(lo), high(hi) {}
	
	Node(const vector<int>& vec, int lo, int hi) : low(lo), high(hi) {
		if(low + 1 < high) {
			int mid = (low + high) / 2;
			l = new Node(vec, low, mid); 
			r = new Node(vec, mid, high);
			value = f(l->value, r->value); // ?
		} else {
			value = vec[low];
		}
	}
	
	int query(int L, int R) {
		if(R <= low || high <= L) return 0; // ?
		if(L <= low && high <= R) return value;
		push();
		return f(l->query(L, R), r->query(L, R)); // ?
	}
	
	void set(int L, int R, int x) {
		if(R <= low || high <= L) return;
		if(L <= low && high <= R) {
			mset = value = x, madd = 0;
		} else {
			push();
			l->set(L, R, x), r->set(L, R, x);
			value = f(l->value, r->value);
		}
	}
	
	void add(int L, int R, int x) {
		if(R <= low || high <= L) return;
		if(L <= low && high <= R) {
			if(mset != INF) {
				mset += x;
			} else {
				madd += x;
			}
			value += x;
		} else {
			push();
			l->add(L, R, x), r->add(L, R, x);
			value = f(l->value, r->value);
		}
	}
	
	void push() {
		if(!l) {
			int mid = (low + high) / 2;
			l = new Node(low, mid);
			r = new Node(mid, high);		
		}
		if(mset != INF) {
			l->set(low, high, mset), r->set(low, high, mset);
			mset = INF; // ?
		} else if(madd != 0) {
			l->add(low, high, madd), r->add(low, high, madd);
			madd = 0; // ?
		}
	}
	
} *tree;

struct HLD {
	
	const bool VALS_EDGES = true; // ?

	vector<pair<int, int>> adj[N]; // ?

	int par[N], siz[N], depth[N], root[N], pos[N], timer = 0;
	
	HLD() {
		for(int i = 0; i < N; ++i) {
			par[i] = -1;
			siz[i] = 1;
		}
	}
	
	void add_edge(int u, int v, int c) {	
		adj[u].push_back({c, v});
		adj[v].push_back({c, u});
	}

	int lca(int u, int v) {
		for(; root[u] != root[v]; v = par[root[v]]) {
			if(depth[root[u]] > depth[root[v]]) {
				swap(u, v);
			}
		}
		return (depth[u] < depth[v]) ? u : v;
	}

	int dist(int u, int v) {
		return depth[u] + depth[v] - 2 * depth[lca(u, v)];
	}	

	template<class B> void process(int u, int v, B op) {
		for(; root[u] != root[v]; v = par[root[v]]) {
			if(depth[root[u]] > depth[root[v]]) {
				swap(u, v);
			}
			op(pos[root[v]], pos[v] + 1);
		}
		if(depth[u] > depth[v]) {
			swap(u, v);
		}
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}

	void modify_path(int u, int v, int val) {
		process(u, v, [&](int L, int R) {
			tree->add(L, R, val);
		});
	}

	int query_path(int u, int v) {
		int res = 0; // ?
		process(u, v, [&](int L, int R) {
			res = f(res, tree->query(L, R)); // ?
		});
		return res;
	}

	int query_subtree(int v) {
		return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}

	void dfs_siz(int v) {
		if(par[v] != -1) {		
			adj[v].erase(find_if(adj[v].begin(), adj[v].end(), [&](const pair<int, int>& ele) {
				return ele.second == par[v];
			}));		
		}
		for(auto& [c, u] : adj[v]) {
			par[u] = v;
			depth[u] = depth[v] + 1;
			dfs_siz(u);
			siz[v] += siz[u];
			if(siz[u] > siz[adj[v][0].second]) {
				swap(u, adj[v][0].second); // ?
				swap(c, adj[v][0].first);
			}
		}
	}

	void dfs_hld(int v) {
		pos[v] = timer++;
		for(const auto& [c, u] : adj[v]) {
			root[u] = (u == adj[v][0].second ? root[v] : u);			
			dfs_hld(u);			
			modify_path(v, u, c);
		}
	}
	
} hld;

int main() {	
	int n, q;
	scanf("%d%d", &n, &q);	
	for(int i = 0; i < n - 1; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		--u, --v;	
		hld.add_edge(u, v, c);
	}
	tree = new Node(0, n);	
	hld.dfs_siz(0);
	hld.dfs_hld(0);	
	while(q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		printf("%d\n", hld.query_path(u, v));
	}
	return 0;
}
