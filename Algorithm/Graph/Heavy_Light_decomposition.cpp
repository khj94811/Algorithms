// https://www.acmicpc.net/problem/13510
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
struct Edge {
	int u, v, w;
	Edge() {};
	Edge(int u, int v, int w) : u(u), v(v), w(w) {};
};
const int MAXN = 1e5 + 5;
int dep[MAXN], p[MAXN][20], chain[MAXN], child[MAXN];
int num[MAXN];
int dn, n, m;
vector<vector<pair<int, int>>> Graph;
vector<int> tree;
vector<Edge> vt;
void dfs(int x, int par) {
	p[x][0] = par;
	child[x] = 1;
	for (int i = 0; i < Graph[x].size(); i++) {
		int next = Graph[x][i].first;
		if (next != par) {
			dep[next] = dep[x] + 1;
			dfs(next, x);
			child[x] += child[next];
		}
	}
}
void HLD(int x, int par, int cnum) {
	num[x] = ++dn;
	chain[dn] = cnum;
	int idx = -1;
	for (int i = 0; i < Graph[x].size(); i++) {
		int y = Graph[x][i].first;
		if (y != par && (idx == -1 || child[y] > child[idx])) idx = y;
	}
	if (idx != -1) HLD(idx, x, cnum);
	for (int i = 0; i < Graph[x].size(); i++) {
		int y = Graph[x][i].first;
		if (y != par && y != idx) HLD(y, x, y);
	}
}

int lca(int u, int v){
	if(dep[u] > dep[v])	swap(u, v);
	for(int i = 19; i >= 0; i--){
		int diff = dep[v] - dep[u];
		if(diff >= (1 << i))	v = p[v][i];
	}
	if(u == v)	return u;
	for(int i = 19; i >= 0; i--){
		if(p[u][i] != p[v][i]){
			u = p[u][i];
			v = p[v][i];
		}
	}
	return p[u][0];
}

void update(int node, int start, int end, int index, int val) {
	if (index >end|| index <start) return;
	if (start == end) {
		tree[node] = val; return;
	}
	update(node * 2, start, (start + end) / 2, index, val);
	update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}
int query(int node, int start, int end, int i, int j) {
	if (i > end || j < start) return 0;
	if (i <= start && end <= j) return tree[node];
	return max(query(node * 2, start, (start + end) / 2, i, j), query(node * 2 + 1, (start + end) / 2 + 1, end, i, j));
}
void init() {
	dfs(1, 0); HLD(1, 0, 1);
	for(int i = 1; i <= 19; i++){
		for(int j = 1; j <= n; j++){
			p[j][i] = p[p[j][i - 1]][i - 1];
		}
	}
	for (int i = 0; i < vt.size(); i++) {
		int u = vt[i].u, v = vt[i].v, w = vt[i].w;
		if (p[u][0] == v) swap(u, v), swap(vt[i].u, vt[i].v);
		update(1, 1, n, num[v], w);
	}
}
int hquery(int u, int v) {
	if (dep[u] > dep[v]) swap(u, v);
	int ret = 0;
	u = num[u], v = num[v];
	while (chain[u] != chain[v]) {
		ret = max(ret, query(1, 1, n, num[chain[v]], v));
		v = num[p[chain[v]][0]];
	}
	ret = max(ret, query(1, 1, n, u + 1, v));
	return ret;
}
int main() {
	scanf("%d", &n);
	Graph.resize(n + 1);
	int tree_size = n * 4;
	tree.resize(tree_size);
	for (int i = 0; i < n - 1; i++) {
		int u, v, w; scanf("%d %d %d", &u, &v, &w);
		vt.emplace_back(u, v, w);
		Graph[u].push_back({ v,w });
		Graph[v].push_back({ u,w });
	}
	init();
	scanf("%d", &m);
	for (int i = 0; i < m; i++) {
		int q, u, v; scanf("%d %d %d", &q, &u, &v);
		if (q == 1) {
			int idx = u,c = v;
			u = vt[idx - 1].u, v = vt[idx - 1].v;
			update(1, 1, n, num[v], c);
		}
		else {
			int LCA = lca(u, v);
			int ans = max(hquery(u, LCA), hquery(v, LCA));
			printf("%d\n", ans);
		}
	}
	return 0;
}