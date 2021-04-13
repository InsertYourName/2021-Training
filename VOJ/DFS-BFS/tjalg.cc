#include <bits/stdc++.h>

using namespace std;

const int N = 10005;

vector<int> adj[N], rev_adj[N];

bool used[N];

vector<int> order{}, comps{};

void dfs1(int u) {
	if(used[u]) return;
	used[u] = true;
	for(int v : adj[u]) dfs1(v);
	order.push_back(u);
}

void dfs2(int u) {
	if(used[u]) return;
	used[u] = true;
	comps.push_back(u);
	for(int v : rev_adj[u]) dfs2(v);
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		adj[u].push_back(v);
		rev_adj[v].push_back(u);
	}
	for(int i = 0; i < n; ++i) {
		used[i] = false;
	}
	for(int i = 0; i < n; ++i) {
		if(not used[i]) dfs1(i);
	}
	for(int i = 0; i < n; ++i) {
		used[i] = false;
	}
	int answer = 0;
	for(int i = 0; i < n; ++i) {
		int u = order[n - 1 - i];
		dfs2(u);
		answer += (not comps.empty());
		comps.clear();
	}
	printf("%d\n", answer);
	return 0;
}
