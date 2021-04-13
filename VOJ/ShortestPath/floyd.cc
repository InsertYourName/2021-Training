#include <bits/stdc++.h>

using namespace std;

const int INF = int(1e9) + 2110;

const int N = 105;

vector<pair<int, int>> adj[N]; // {weight, to}

int dist[N], par[N];

int main() {
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for(int i = 0; i < m; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		--u, --v;
		adj[u].emplace_back(c, v);
		adj[v].emplace_back(c, u);
	}
	while(q--) {
		int op, u, v;
		scanf("%d%d%d", &op, &u, &v);
		--u, --v;
		for(int i = 0; i < n; ++i) {
			par[i] = -1;
			dist[i] = INF;
		}
		dist[u] = 0;		
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> Q;
		Q.push({dist[u], u});
		#define u ____dont_use_u____
		while(not Q.empty()) {
			auto [du, u] = Q.top();
			Q.pop();
			if(dist[u] != du) continue;
			for(const auto& [weight, to] : adj[u]) {
				if(dist[u] + weight < dist[to]) {
					dist[to] = dist[u] + weight;
					par[to] = u;
					Q.push({dist[to], to});
				}
			}
		}
		#undef u		
		if(op == 0) {
			printf("%d\n", dist[v]);
		} else if(op == 1) {
			vector<int> path{};		
			for(; v^u; v = par[v]) {
				path.push_back(v);																	
			}
			path.push_back(u);
			reverse(path.begin(), path.end());
			printf("%d ", (int)path.size());
			for(int p : path) {
				printf("%d ", p + 1);
			}
			printf("\n");
		} else assert(false);
	}
	return 0;
}
