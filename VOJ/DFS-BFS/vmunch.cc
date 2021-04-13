#include <bits/stdc++.h>

using namespace std;

const int INF = int(1e9) + 2110;

const int N = 105;

const int dx[4] = {1, -1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

char s[N][N];

int dist[N][N];

int r, c;

int inside(int x, int y) {
	return x >= 0 && x < r && y >= 0 && y < c && s[x][y] == '.';
}

int main() {
	scanf("%d%d", &r, &c);
	int sx, sy, tx, ty;
	for(int i = 0; i < r; ++i) {
		scanf("%s", s[i]);
		for(int j = 0; j < c; ++j) {
			dist[i][j] = INF;
			if(s[i][j] == 'B') {
				s[i][j] = '.';
				sx = i, sy = j;
			}
			if(s[i][j] == 'C') {
				s[i][j] = '.';
				tx = i, ty = j;
			}
		}
	}	
	queue<pair<int, int>> Q;
	Q.push({sx, sy});
	dist[sx][sy] = 0;
	while(not Q.empty()) {
		auto [cx, cy] = Q.front();
		Q.pop();
		if(s[cx][cy] != '.') continue;
		s[cx][cy] = '@';
		for(int k = 0; k < 4; ++k) {
			if(inside(cx + dx[k], cy + dy[k])) {
				if(dist[cx][cy] + 1 < dist[cx + dx[k]][cy + dy[k]]) {
					dist[cx + dx[k]][cy + dy[k]] = dist[cx][cy] + 1;
					Q.push({cx + dx[k], cy + dy[k]});
				}
			}
		}	
	}
	printf("%d\n", dist[tx][ty]);
	return 0;
}
