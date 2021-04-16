#include <bits/stdc++.h>

using namespace std;

const int N = 100005;
int a[N], n;

int odd[N], even[N], p, q;

void solve() {
	p = 0, q = 0;
	scanf("%d", &n);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int i = 0; i < n; ++i) {
		if(a[i] % 2 == 0) {
			even[q++] = a[i];
		} else {
			odd[p++] = a[i];
		}
	}
	for(int i = 0; i < q; ++i) {
		printf("%d ", even[i]);
	}
	for(int i = 0; i < p; ++i) {
		printf("%d ", odd[i]);		
	}	
	printf("\n");
}

int main() {	
	int t;
	scanf("%d", &t);
	while(t--) {
		solve();
	}
	return 0;
}
