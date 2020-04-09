struct Edge{
	int v, cap, rev;
	Edge(){}
	Edge(int v, int cap, int rev) : v(v), cap(cap), rev(rev){}
};
int TC, S, T, N, M, level[MAX], work[MAX];
vector<Edge> adj[MAX];

void addEdge(int u, int v, int cap){
	adj[u].emplace_back(v, cap, (int)adj[v].size());
	adj[v].emplace_back(u, 0, (int)adj[u].size() - 1);
}

bool bfs(){
	memset(level, -1, sizeof(level));
	queue<int> q;
	q.push(S);	level[S] = 0;
	while(!q.empty()){
		int cur = q.front();
		q.pop();
		for(int i = 0; i < adj[cur].size(); i++){
			int next = adj[cur][i].v;
			int cap = adj[cur][i].cap;
			if(cap > 0 && level[next] == -1){
				level[next] = level[cur] + 1;
				q.push(next);
			}
		}
	}
	return level[T] != -1;
}

int dfs(int cur, int flow){
	if(cur == T)	return flow;
	for(int &i = work[cur]; i < adj[cur].size(); i++){
		int next = adj[cur][i].v;
		int cap = adj[cur][i].cap;
		int rev = adj[cur][i].rev;
		if(cap > 0 && level[next] == level[cur] + 1){
			int cf = dfs(next, min(flow, cap));
			if(cf > 0){
				adj[cur][i].cap -= cf;
				adj[next][rev].cap += cf;
				return cf;
			}
		}
	}
	return 0;
}

int solve(){
	int tflow = 0;
	while(bfs()){
		memset(work, 0, sizeof(work));
		while(true){
			int flow = dfs(S, 1e9);
			if(!flow)	break;
			tflow += flow;
		}
	}
	return tflow;
}
