#include <bits/stdc++.h>

using namespace std;

const int INF = int(1e9) + 2110;

const int N = 18;
int c[N][N];
int n;

int dp[1 << N][N];

int rec(int mask, int end) {
	if(mask == 0) return 0;
	int& res = dp[mask][end];
	if(res != 0) return res;
	res = INF;	
	for(int i = 0; i < n; ++i) {
		if(mask & (1 << i)) {
			res = min(res, rec(mask ^ (1 << i), i) + c[i][end]);
		}
	}
	return res;
}

int main() {	
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		for(int j = 0; j < n; ++j) {
			scanf("%d", &c[i][j]);
		}
	}
	int answer = INF;
	for(int i = 0; i < n; ++i) {
		answer = min(answer, rec((1 << n) - 1, i));
	}
	printf("%d\n", answer);
	return 0;
}
