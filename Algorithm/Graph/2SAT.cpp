#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
int N, M;
struct SCC{
    int Vcnt, Ecnt, SZ, totalNumber, sccNumber;
    vector<vector<int>> adj;
    vector<int> vis, fin, scc;
    SCC(){SZ = Vcnt = Ecnt = 0;}
    SCC(int Vcnt, int Ecnt, int SZ) : Vcnt(Vcnt), Ecnt(Ecnt), SZ(SZ){
        init();
    }
    void init(){
        adj.resize(SZ + 1);
        vis.assign(SZ + 1, 0);fin.assign(SZ + 1, 0);
        scc.assign(SZ + 1, 0);
        totalNumber = sccNumber = 0;
    }
    /* Odd : NOT, Even : TRUE*/
    int conv(int node){
        if(node < 0)    return -node * 2 - 1;
        return node * 2;
    }
    void addEdge(int u, int v){
        adj[u].push_back(v);
    }
    void satEdge(int u, int v){
        adj[conv(-u)].push_back(conv(v));
        adj[conv(-v)].push_back(conv(u));
    }
    stack<int> stk;
    int dfs(int cur){
        int ret = vis[cur] = ++totalNumber;
        stk.push(cur);
        for(auto &next : adj[cur]){
            if(!vis[next])  ret = min(ret, dfs(next));
            else if(!fin[next]) ret = min(ret, vis[next]);
        }
        if(ret == vis[cur]){
            ++sccNumber;
            while(true){
                int t = stk.top();
                stk.pop();
                fin[t] = 1;
                scc[t] = sccNumber;
                if(t == cur)    break;
            }
        }
        return ret;
    }
    int solve(){
        for(int i = 1; i <= 2 * Vcnt; i++){
            if(!vis[i]) dfs(i);
        }
        for(int i = 1; i <= Vcnt; i++){
            if(scc[conv(i)] == scc[conv(-i)])   return false;
        }
        return true;
    }
};

int main(){
    scanf("%d %d", &N, &M);
    SCC sat(N, M, 2 * N);
    for(int i = 1; i <= M; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        sat.satEdge(u, v);
    }
    vector<int> ans(N + 1, -1);
    if(sat.solve()){
        puts("1");
        vector<pii> vt;
        for(int i = 1; i <= sat.SZ; i++){
            vt.push_back({sat.scc[i], i});
        }
        sort(vt.begin(), vt.end());
        for(int i = sat.SZ; i >= 1; i--){
            int id = vt[i - 1].second;
            if(ans[(id + 1) / 2] == -1){
                ans[(id + 1) / 2] = (id & 1);
            }
        }
        for(int i = 1; i <= N; i++){
            printf("%d ", ans[i]);
        }
    }
    else{
        puts("0");
    }
    return 0;
}