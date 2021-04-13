#include <bits/stdc++.h>

using namespace std;

const int N = 105, M = 10005;

int dist[N][N], order[M];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i) {
		scanf("%d", &order[i]);
		--order[i];
	}
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &dist[i][j]);
		}
	}
	for(int k = 0; k < n; ++k) {
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < n; ++j) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
	int answer = 0;
	for(int i = 0; i < m - 1; ++i) {
		answer += dist[order[i]][order[i + 1]];
	}
	printf("%d\n", answer);
	return 0;
}
