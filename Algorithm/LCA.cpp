#include <bits/stdc++.h>
using namespace std;
int N, M, p[20][100002], depth[100002];
vector<int> adj[100002];

void dfs(int cur, int par){
    for(auto &next : adj[cur]){
        if(next == par) continue;
        depth[next] = depth[cur] + 1;
        p[0][next] = cur;
        dfs(next, cur);
    }
}

int lca(int u, int v){
    if(depth[u] > depth[v]) swap(u, v);
    for(int i = 19; i >= 0; i--){
        int diff = depth[v] - depth[u];
        if(diff & (1 << i)){
            v = p[i][v];
        }
    }
    if(u == v)  return u;
    for(int i = 19; i >= 0; i--){
        if(p[i][u] != p[i][v]){
            u = p[i][u];
            v = p[i][v];
        }
    }
    return p[0][u];
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N - 1; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, 0);
    scanf("%d", &M);
    for(int i = 1; i < 20; i++){
        for(int j = 1; j <= N; j++){
            p[i][j] = p[i - 1][p[i - 1][j]];
        }
    }
    while(M--){
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", lca(u, v));
    }
    return 0;
}