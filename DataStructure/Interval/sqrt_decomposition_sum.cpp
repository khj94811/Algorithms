#include <cstdio>
#include <algorithm>
#include <cmath>
#define N_MAX 1000001
using namespace std;
typedef long long ll;
int N, M, K, sz, a[N_MAX];
ll bucket[1002];

void init() {
	sz = sqrt(N);
	for (int i = 0; i < N; i++)
		bucket[i / sz] += a[i];
}

ll query(int lo, int hi) {
	ll ret = 0;
	while (lo % sz != 0 && lo <= hi)
		ret += a[lo++];
	while ((hi + 1) % sz != 0 && lo <= hi)
		ret += a[hi--];
	while (lo <= hi) {
		ret += bucket[lo / sz];
		lo += sz;
	}
	return ret;
}

void update(int pos, ll val) {
	ll diff = val - a[pos];
	a[pos] = val;
	bucket[pos / sz] += diff;
}

int main() {
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++)
		scanf("%d", a + i);
	init();
	for (int i = 0; i < M + K; i++) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		if (u == 1)
			update(v - 1, w);
		else
			printf("%lld\n", query(v - 1, w - 1));
	}
	return 0;
}