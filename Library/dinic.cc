#include <bits/stdc++.h>

using namespace std;

const long long INF = (long long)2e18 + 2110;

const int N = 100100;

struct Dinic {

	struct Edge {
		int to, rev;
		long long cap, flow;
	};

	vector<Edge> adj[N];

	int dist[N], ptr[N];

	bool bfs(int s, int t) {
		memset(dist, -1, sizeof dist);
		dist[s] = 0;
		queue<int> Q;
		Q.push(s);
		while(not Q.empty() && dist[t] == -1) {
			int u = Q.front();
			Q.pop();
			for(Edge e : adj[u]) {
				if(dist[e.to] == -1 && e.cap != e.flow) {
					dist[e.to] = dist[u] + 1;
					Q.push(e.to);
				}
			}
		}
		return dist[t] != -1;
	}

	long long augment(int u, long long amt, int t) {
		if(u == t) return amt;
		for(; ptr[u] < (int) adj[u].size(); ++ptr[u]) {
			Edge& e = adj[u][ptr[u]];
			if(dist[e.to] == dist[u] + 1 && e.cap != e.flow) {
				long long flow = augment(e.to, min(amt, e.cap - e.flow), t);
				if(flow != 0) {
					e.flow += flow;
					adj[e.to][e.rev].flow -= flow;
					return flow;
				}
			}
		}
		return 0;
	}

	long long maxflow(int source, int sink) {
		long long flow = 0;
		while(bfs(source, sink)) {
			memset(ptr, 0, sizeof ptr);
			while(long long df = augment(source, INF, sink)) {
				flow += df;
			}
		}
		return flow;
	}

	void add_edges(int u, int v, long long cap = 1, long long rev_cap = 0) {
		adj[u].push_back((Edge){v, (int) adj[v].size(), cap, 0});
		adj[v].push_back((Edge){u, (int) adj[u].size() - 1 , rev_cap, 0});
	}
};

int main() {
	Dinic network;
	network.add_edges(0, 1, 75);
	network.add_edges(0, 2, 50);
	network.add_edges(1, 2, 40);
	network.add_edges(1, 3, 50);
	network.add_edges(2, 3, 30);
	long long flow = network.maxflow(0, 3);
	printf("%lld\n", flow);
	return 0;
}
