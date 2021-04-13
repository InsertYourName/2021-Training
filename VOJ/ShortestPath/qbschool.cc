#include <bits/stdc++.h>

using namespace std;

const long long INF = (long long)1e18 + 2110;

const int N = 5010;

vector<pair<int, int>> adj[N]; // {weight, to}

int n;

long long dist[N], cnt[N];

int main() {
	int m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i) {
		int k, u, v, c;
		scanf("%d%d%d%d", &k, &u, &v, &c);
		--u, --v;
		adj[u].emplace_back(c, v);
		if(k == 2) {
			adj[v].emplace_back(c, u);
		}
	}
	for(int i = 0; i < n; ++i) dist[i] = INF;
	priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> Q;
	dist[0] = 0;
	cnt[0] = 1;
	Q.push({dist[0], 0});
	while(not Q.empty()) {
		auto [du, u] = Q.top();
		Q.pop();
		if(du != dist[u]) continue;
		for(const auto& [weight, to] : adj[u]) {
			if(dist[u] + weight < dist[to]) {
				dist[to] = dist[u] + weight;
				cnt[to] = cnt[u];
				Q.push({dist[to], to});
			} else if(dist[u] + weight == dist[to]) {
				cnt[to] += cnt[u];
			}
		}
	}
	printf("%lld %lld\n", dist[n - 1], cnt[n - 1]);
	return 0;
}
