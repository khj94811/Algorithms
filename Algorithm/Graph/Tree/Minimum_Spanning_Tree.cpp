#include <bits/stdc++.h>
using namespace std;
int V, E, p[10005];
vector<pair<int, pair<int, int>>> vt;

int find(int x){
	if(p[x] == x)	return x;
	return p[x] = find(p[x]);
}

bool Merge(int u, int v){
	u = find(u);
	v = find(v);
	if(u == v)	return false;
	p[u] = v;
	return true;
}

int main(){
	scanf("%d %d", &V, &E);
	for(int i = 1; i <= V; i++)
		p[i] = i;
	for(int i = 0; i < E; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		vt.push_back({w, {u, v}});
	}
	sort(vt.begin(), vt.end());
	int ans = 0;
	for(int i = 0; i < E; i++){
		int u = vt[i].second.first;
		int v = vt[i].second.second;
		int w = vt[i].first;
		if(Merge(u, v)){
			ans += w;
		}
	}
	printf("%d\n" ,ans);
	return 0;
}