#include <iostream>
using namespace std;

const int MAX = 1e5;
struct DSU{
    int parent[MAX];
    DSU(){
        for(register int i = 0; i < MAX; ++i){
            parent[i] = -1;
        }
    }
    DSU(int sz){
        for(register int i = 0; i < sz; ++i){
            parent[i] = -1;
        }
    }
    int find(int x){
        return (parent[x] < 0 ? x : parent[x] = find(parent[x]));
    }
    bool merge(int u, int v){
        u = find(u), v = find(v);
        if(u == v)  return false;
        parent[v] += parent[u];
        parent[u] = v;
        return true;
    }
    int size(int x){
        return -parent[find(x)];
    }
};

int main(){
    int n;  cin >> n;
    DSU D(n + 1);
    for(int i = 0; i < 3; i++){
        int u, v;
        cin >> u >> v;
        D.merge(u, v);
    }
    int x; cin >> x;
    cout << D.size(x) << endl;
    return 0;
}
