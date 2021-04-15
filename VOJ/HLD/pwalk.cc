// Draft !

#include <bits/stdc++.h>

using namespace std;

const int INF = int(2e9) + 2110;

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
			l->set(L, R, x);
			r->set(L, R, x);
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
			l->add(L, R, x);
			r->add(L, R, x);
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
			l->set(low, high, mset);
			r->set(low, high, mset);
			mset = INF; // ?
		} else if(madd != 0) {
			l->add(low, high, madd);
			r->add(low, high, madd);
			madd = 0; // ?
		}
	}
};

const bool VALS_EDGES = true;

const int N = (1 << 18);

vector<int> adj[N];
vector<pair<int, int>> cost[N];

int par[N], siz[N], depth[N], rt[N], pos[N], timer = 0;

Node* tree;

int n;

void dfs_siz(int v) {
	if(par[v] != -1) {
		auto it = find(adj[v].begin(), adj[v].end(), par[v]);		
		adj[v].erase(it);		
	}
	for(int& u : adj[v]) {
		par[u] = v;
		depth[u] = depth[v] + 1;
		dfs_siz(u);
		siz[v] += siz[u];
		if(siz[u] > siz[adj[v][0]]) {
			swap(u, adj[v][0]); // ?
		}
	}
}

void dfs_hld(int v) {
	pos[v] = timer++;
	for(int u : adj[v]) {
		rt[u] = (u == adj[v][0] ? rt[v] : u);
		dfs_hld(u);
	}
}

int lca(int u, int v) {
	for(; rt[u] != rt[v]; v = par[rt[v]]) {
		if(depth[rt[u]] > depth[rt[v]]) swap(u, v);
	}
	return depth[u] < depth[v] ? u : v;
}

int dist(int u, int v) {
	return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

template<class B> void process(int u, int v, B op) {
	for(; rt[u] != rt[v]; v = par[rt[v]]) {
		if(depth[rt[u]] > depth[rt[v]]) swap(u, v);
		op(pos[rt[v]], pos[v] + 1);
	}
	if(depth[u] > depth[v]) swap(u, v);
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

void dfs_cost(int v, int p = 0) {
	for(const auto& [c, u] : cost[v]) {
		if(u == p) continue;
		modify_path(v, u, c);
		dfs_cost(u, v);
	}
}

int main() {	
	int q;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n - 1; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		--u, --v;		
		adj[u].push_back(v);
		adj[v].push_back(u);
		cost[u].push_back({c, v});
		cost[v].push_back({c, u});
	}
	tree = new Node(0, n);
	for(int i = 0; i < n; ++i) {
		par[i] = -1;
		siz[i] = 1;		
	}
	dfs_siz(0);
	dfs_hld(0);	
	dfs_cost(0);
	while(q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		printf("%d\n", query_path(u, v));
	}
	return 0;
}
