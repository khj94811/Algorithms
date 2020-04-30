#include <bits/stdc++.h>
using namespace std;
struct Edge{
	int v, cap, cost, rev;
	Edge(){}
	Edge(int v, int cap, int cost, int rev) : v(v), cap(cap), cost(cost), rev(rev){}
};
int N, M;
const int MAX = 1005;

struct MCMF{
	int SZ, S, T;
	vector<vector<Edge>> adj;
	vector<int> prv, pdx;
	MCMF(int sz){
		adj.resize(sz + 2);
		prv.assign(sz + 2, 0);
		pdx.assign(sz + 2, 0);
		S = 0, T = sz + 1;
	}
	void addEdge(int u, int v, int cap, int cost){
		adj[u].emplace_back(v, cap, cost, (int)adj[v].size());
		adj[v].emplace_back(u, 0, -cost, (int)adj[u].size() - 1);
	}
	bool spfa(){
		vector<int> dist(N + 2, 1e9);
		vector<int> inQ(N + 2, 0);
		queue<int> q;
		q.push(S);	inQ[S] = 1;	dist[S] = 0;
		while(!q.empty()){
			int cur = q.front();
			inQ[cur] = 0;
			q.pop();
			for(int i = 0; i < adj[cur].size(); i++){
				int next = adj[cur][i].v;
				int cap = adj[cur][i].cap;
				int ndist = adj[cur][i].cost;
				if(cap && dist[next] > dist[cur] + ndist){
					dist[next] = dist[cur] + ndist;
					prv[next] = cur, pdx[next] = i;
					if(!inQ[next])	q.push(next), inQ[next] = 1;
				}
			}
		}
		return dist[T] != 1e9;
	}

	int solve(){
		int tflow = 0, tcost = 0;
		while(spfa()){
			int flow = 1e9;
			for(int i = T; i != S; i = prv[i]){
				flow = min(flow, adj[prv[i]][pdx[i]].cap);
			}
			for(int i = T; i != S; i = prv[i]){
				adj[prv[i]][pdx[i]].cap -= flow;
				adj[i][adj[prv[i]][pdx[i]].rev].cap += flow;
				tcost += flow * adj[prv[i]][pdx[i]].cost;
			}
			tflow += flow;
		}
		return tcost;
	}
};

int main(){
	scanf("%d %d", &N, &M);
	MCMF mf(N);
	mf.addEdge(mf.S, 1, 2, 0);
	mf.addEdge(N, mf.T, 2, 0);
	for(int i = 0; i < M; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		mf.addEdge(u, v, 1, w);
		mf.addEdge(v, u, 1, w);
	}
	printf("%d\n", mf.solve());
	return 0;
}