#include <bits/stdc++.h>

using namespace std;

const int INF = int(1e9) + 2110;

const int N = 1005;

vector<int> adj[N];

int n;

int val[N], comp[N], numComps;

int timer = 0;

stack<int> stk{};

bool used[N];

int dfs(int u) {
	int low = val[u] = ++timer;
	stk.push(u);
	for(int v : adj[u]) if(comp[v] < 0) {
		low = min(low, val[v] ?: dfs(v));
	}
	if(low == val[u]) {
		int x;
		do {
			x = stk.top();
			stk.pop();
			comp[x] = numComps;
		} while(x != u);
		numComps++;
	}
	return val[u] = low;
}

int main() {
	int m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		adj[u].push_back(v);		
	}
	for(int i = 0; i < n; ++i) {
		comp[i] = -1;
		used[i] = true;
	}
	numComps = 0;
	for(int i = 0; i < n; ++i) {
		if(comp[i] < 0) dfs(i);
	}		
	for(int i = 0; i < n; ++i) {
		for(int v : adj[i]) {
			if(comp[v] != comp[i]) {
				used[comp[v]] = false;
			}
		}
	}
	int answer = 0;
	for(int i = 0; i < numComps; ++i) {
		answer += used[i] == true;
	}
	printf("%d\n", answer);
	return 0;
}
