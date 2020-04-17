// https://www.acmicpc.net/problem/8217
// 유명한 유성 문제.
#include <bits/stdc++.h>
using namespace std;
#define MAX 300002
typedef long long ll;
struct Query{
	int l, r, u;
	Query(){}
	Query(int l, int r, int u) : l(l), r(r), u(u){}
};
int N, M, K, a[MAX], b[MAX], lo[MAX], hi[MAX];
ll BIT[MAX * 2];
vector<Query> vt;
vector<int> pos[MAX];

void update(int pos, int val){
	for(int i = pos; i <= M; i += (i & -i))
		BIT[i] += 1LL * val;
}

ll query(int pos){
	ll ret = 0;
	for(int i = pos; i >= 1; i -= (i & -i))
		ret += BIT[i];
	return ret;
}

void add(int idx){
	Query q = vt[idx];
	int l = q.l, r = q.r, val = q.u;
	if(l <= r){
		update(l, val);
		update(r + 1, -val);
	}
	else{
		swap(l, r);
		update(l + 1, -val);
		update(1, val);
		update(r, val);
	}
}

int main(){
	scanf("%d %d", &N, &M);
	for(int i = 1; i <= M; i++){
		int d;
		scanf("%d", &d);
		pos[d].push_back(i);
	}
	for(int i = 1; i <= N; i++)
		scanf("%d", b + i);
	scanf("%d", &K);
	vt.emplace_back(0, 0, 0);
	for(int i = 1; i <= K; i++){
		int l, r, u;
		scanf("%d %d %d", &l, &r, &u);
		vt.emplace_back(l, r, u);
	}
	bool fin = true;
	for(int i = 1; i <= N; i++)
		lo[i] = 1, hi[i] = K + 1;
	while(fin){
		vector<vector<int>> qr(K + 1);
		fin = false;
		memset(BIT, 0, sizeof(BIT));
		for(int i = 1; i <= N; i++){
			if(lo[i] < hi[i])	qr[(lo[i] + hi[i]) / 2].push_back(i), fin = true;
		}
		for(int i = 1; i <= K; i++){
			add(i);
			while(qr[i].size()){
				int idx = qr[i].back();
				qr[i].pop_back();
				ll s = 0;
				for(int j = 0; j < pos[idx].size(); j++){
					s += query(pos[idx][j]);
					if(s >= 1LL * b[idx])	break;
				}
				if(s >= 1LL * b[idx])
					hi[idx] = i;
				else
					lo[idx] = i + 1;
			}
		}
	}
	for(int i = 1; i <= N; i++)
		if(lo[i] == K + 1)	puts("NIE");
		else printf("%d\n", lo[i]);
	return 0;
}