#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e4 + 5;
int N, M, vis[MAX], fin[MAX], scc[MAX], gn, sn;
stack<int> stk;
vector<int> adj[MAX], ans[MAX];

int dfs(int cur){
	int ret = vis[cur] = ++gn;
	stk.push(cur);
	for(auto &next : adj[cur]){
		if(!vis[next]){
			ret = min(ret, dfs(next));
		}
		else if(!fin[next]){
			ret = min(ret, vis[next]);
		}
	}
	if(ret == vis[cur]){
		++sn;
		while(true){
			int t = stk.top();
			stk.pop();
			fin[t] = 1;
			scc[t] = sn;
			if(t == cur)	break;
		}
	}
	return ret;
}

int main(){
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= M; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
	}
	for(int i = 1; i <= N; i++){
		if(!vis[i])	dfs(i);
	}
	for(int i = 1; i <= N; i++){
		ans[scc[i]].push_back(i);
	}
	printf("%d\n", sn);
	sort(ans + 1, ans + sn + 1, [](vector<int> u, vector<int> v){
		return u[0] < v[0];
	});
	for(int i = 1; i <= sn; i++){
		for(auto &j : ans[i])
			printf("%d ", j);
		puts("-1");
	}
	return 0;
}