#include <bits/stdc++.h>

using namespace std;

const int INF = int(1e9) + 2110;

const int N = 100005;

vector<int> adj[N];

int n;

int dist[N];

int main() {
	int m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);		
		adj[u].push_back(v);
		adj[u].push_back(w);
	}
	adj[0].push_back(1);
	for(int i = 0; i < n; ++i) dist[i] = INF;
	queue<int> Q{ {0} };
	dist[0] = 0;
	while(not Q.empty()) {
		int u = Q.front();
		Q.pop();
		for(int v : adj[u]) {
			dist[v] = dist[u] + 1;
			Q.push(v);
		}
	}
	for(int i = 1; i <= n; ++i) {
		printf("%d\n", dist[i]);
	}
	return 0;
}
