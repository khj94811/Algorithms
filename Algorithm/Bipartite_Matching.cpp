#include <vits/stdc++.h>
#define MAX 1001
using namespace std;
int N, M, A[MAX], B[MAX], visited[MAX];
vector<vector<int>> adj;

bool dfs(int cur) {
	if (visited[cur])	return false;
	visited[cur] = 1;
	for (auto &next : adj[cur]) {
		if (B[next] == -1 || dfs(B[next])) {
			A[cur] = next;
			B[next] = cur;
			return true;
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		adj.clear();
		scanf("%d %d", &N, &M);
		adj.resize(M + 1);
		memset(B, -1, sizeof(B));
		memset(A, -1, sizeof(A));
		for (int i = 0; i < M; i++) {
			int a, b;
			scanf("%d %d", &a, &b);
			for (int j = a; j <= b; j++)
				adj[i + 1].push_back(j);
		}
		int match = 0;
		for (int i = 1; i <= M; i++) {
			memset(visited, 0, sizeof(visited));
			if (dfs(i))	match++;
		}
		printf("%d\n", match);
	}
}