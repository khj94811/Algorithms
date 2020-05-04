#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5 + 5;
int N, M, p[20][MAX], dep[MAX], W[MAX];
vector<int> adj[MAX], vt;

struct Node{
    int val;
    Node *l, *r;
    Node(int val, Node *l, Node *r) : val(val), l(l), r(r){}
    Node *update(int x, int y, int pos){
        if(pos < x || pos > y)  return this;
        if(x == y){
            return new Node(val + 1, NULL, NULL);
        }
        int mid = (x + y) / 2;
        return new Node(val + 1, l->update(x, mid, pos), r->update(mid + 1, y, pos));
    }
}*seg[MAX];

int query(Node *l, Node *r, Node *par, Node *ppar, int x, int y, int k){
    if(x == y){
        return x;
    }
    int cnt = l->l->val + r->l->val - par->l->val - ppar->l->val;
    int mid = (x + y) / 2;
    if(cnt >= k){
        return query(l->l, r->l, par->l, ppar->l, x, mid, k);
    }
    return query(l->r, r->r, par->r, ppar->r, mid + 1, y, k - cnt);
}

int getNum(int x){
    return upper_bound(vt.begin(), vt.end(), x) - vt.begin();
}

void dfs(int cur, int par){
    seg[cur] = seg[par]->update(1, vt.size(), getNum(W[cur]));
    for(auto &next : adj[cur]){
        if(next == par) continue;
        p[0][next] = cur;
        dep[next] = dep[cur] + 1;
        dfs(next, cur);
    }
}

int lca(int u, int v){
    if(dep[u] > dep[v]) swap(u, v);
    for(int i = 19; i >= 0; i--){
        int diff = dep[v] - dep[u];
        if(diff >= (1 << i)){
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
    scanf("%d %d", &N, &M);
    for(int i = 1; i <= N; i++){
        scanf("%d", W + i);
        vt.push_back(W[i]);
    }
    for(int i = 0; i < N - 1; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    sort(vt.begin(), vt.end());
    vt.erase(unique(vt.begin(), vt.end()), vt.end());
    seg[0] = new Node(0, NULL, NULL);
    seg[0]->l = seg[0]->r = seg[0];
    dfs(1, 0);
    for(int i = 1; i < 20; i++){
        for(int j = 1; j <= N; j++){
            p[i][j] = p[i - 1][p[i - 1][j]];
        }
    }
    while(M--){
        int x, y, k;
        scanf("%d %d %d", &x, &y, &k);
        int anc = lca(x, y);
        printf("%d\n", vt[query(seg[x], seg[y], seg[anc], seg[p[0][anc]], 1, vt.size(), k) - 1]);
    }
    return 0;
}