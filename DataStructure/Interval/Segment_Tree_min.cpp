#include <bits/stdc++.h>
using namespace std;
#define N_MAX 100000
#define SEG_MAX 1 << 18
#define INF 1e9
int N, M, a[N_MAX], seg[SEG_MAX];

void init(int node, int x, int y) {
	if (x == y)	seg[node] = a[x];
	else {
		int mid = (x + y) >> 1;
		init(node * 2, x, mid);
		init(node * 2 + 1, mid + 1, y);
		seg[node] = min(seg[node * 2], seg[node * 2 + 1]);
	}
}

int update(int pos, int val, int node, int x, int y) {
	if (pos < x || pos > y)	return seg[node];
	if (x == y)	return seg[node] = val;
	int mid = (x + y) >> 1;
	int l = update(pos, val, node * 2, x, mid);
	int r = update(pos, val, node * 2 + 1, mid + 1, y);
	return seg[node] = min(l, r);
}

int query(int lo, int hi, int node, int x, int y) {
	if (y < lo || x > hi)	return INF;
	if (lo <= x && y <= hi)	return seg[node];
	int mid = (x + y) >> 1;
	int l = query(lo, hi, node * 2, x, mid);
	int r = query(lo, hi, node * 2 + 1, mid + 1, y);
	return min(l, r);
}

int main() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", a + i);
	init(1, 0, N - 1);
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		int x, u, v;
		scanf("%d %d %d", &x, &u, &v);
		if (x == 1) 
			update(u - 1, v, 1, 0, N - 1);
		else
			printf("%d\n", query(u - 1, v - 1, 1, 0, N - 1));
	}
	return 0;
}