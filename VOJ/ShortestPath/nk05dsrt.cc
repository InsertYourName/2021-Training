// Status: non-tested ...

#include <bits/stdc++.h>

using namespace std;

const int INF = int(1e9) + 2110;

const int N = 105;

vector<pair<int, int>> adj[N];

int dist[N];

int n, m, C;

int ceil(int a, int b) {
	return (a + b - 1) / b;
}

void solve() {
	for(int i = 0; i < N; ++i) {
		adj[i].clear();
		dist[i] = INF;
	}
	scanf("%d%d%d", &n, &m, &C);
	for(int i = 0; i < m; ++i) {
		int u, v, L;
		scanf("%d%d%d", &u, &v, &L);
		--u, --v;
		adj[u].push_back({L, v});
		adj[v].push_back({L, u});
	}
	dist[n - 1] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
	Q.push({dist[n - 1], n - 1});
	while(not Q.empty()) {
		auto [du, u] = Q.top();
		Q.pop();
		if(du != dist[u]) continue;
		for(const auto& [len, to] : adj[u]) {
			if(dist[u] + len <= C) {
				if(dist[to] > dist[u] + len) {
					dist[to] = dist[u] + len;
					Q.push({dist[to], to});					
				}
			} else {
				if(2 * len > C) continue;
				int t = ceil(dist[u] + len - C, C - 2 * len);
				int dt = dist[u] + len + t * (len * 2);
				if(dist[to] > dt) {
					dist[to] = dt;
					Q.push({dist[to], to});					
				}
			}
		}
	}	
	printf("%d\n", dist[0]);
}

int main() {	
	int t;
	scanf("%d", &t);
	while(t--) {
		solve();
	}
	return 0;
}
