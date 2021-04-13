#include <bits/stdc++.h>

using namespace std;

const int N = 1005;
const int LOG = 20;

vector<pair<int, int>> adj[N];

int anc[N][LOG], summa[N][LOG];
int depth[N], tin[N], tout[N];

int n, timer = 0;

void pre(int cur = 0, int prv = 0) {
	for(const auto& [len, nxt] : adj[cur]) {
		if(nxt == prv) continue;
		summa[nxt][0] = len;
		pre(nxt, cur);
	}
}

void dfs(int cur = 0, int par = 0, int dep = 0) {
	tin[cur] = ++timer;
	anc[cur][0] = par;
	depth[cur] = dep;
	for(int i = 1; i < LOG; ++i) {
		anc[cur][i] = anc[anc[cur][i - 1]][i - 1];
		summa[cur][i] = summa[cur][i - 1] + summa[anc[cur][i - 1]][i - 1];
	}
	for(const auto& [w, v] : adj[cur]) {
		if(v == par) continue;
		dfs(v, cur, dep + 1);
	}
	tout[cur] = ++timer;
}

bool is_ancestor(int a, int b) {
	return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
	if(is_ancestor(a, b)) return a;
	if(is_ancestor(b, a)) return b;
	for(int i = LOG - 1; i >= 0; --i) {
		if(not is_ancestor(anc[a][i], b)) {
			a = anc[a][i];
		}
	}
	return anc[a][0];
}

int query(int a, int b) {
	int m = lca(a, b);
	int answer = 0;
	for(int rep = 0; rep < 2; ++rep) {
		for(int i = LOG - 1; i >= 0; --i) { // ?
			if(is_ancestor(m, anc[a][i])) {				
				answer += summa[a][i];
				a = anc[a][i];
			}
		}
		swap(a, b);
	}
	return answer;
}

int main() {
	int q;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n - 1; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		--u, --v;
		adj[u].emplace_back(c, v);
		adj[v].emplace_back(c, u);
	}
	pre();
	dfs();
	while(q--) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		printf("%d\n", query(u, v));
	}
	return 0;
}
