#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
ll N;
pll A[200005], s[200005];

int ccw(pll x, pll y, pll z){
	ll t = (y.first - x.first) * (z.second - x.second) - (y.second - x.second) * (z.first - x.first);
	return t < 0 ? -1 : t > 0 ? 1 : 0;
}

ll dis(pll x, pll y){
	return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
}

bool cmp(pll x, pll y){
	if (ccw(A[0], x, y)) return ccw(A[0], x, y) < 0;
	return abs(x.first - A[0].first) + abs(x.second - A[0].second) < abs(y.first - A[0].first) + abs(y.second - A[0].second);
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%lld", &N);
        for(int i = 0; i < N; i++){
            scanf("%lld %lld", &A[i].first, &A[i].second);
            if(A[i] < A[0]) swap(A[0], A[i]);
        }
        ll mx = -1, sn = 0;
        sort(A + 1, A + N, cmp);
        s[sn++] = A[0];
        for(int i = 1; i < N; i++){
            while (sn > 1 && ccw(s[sn - 2], s[sn - 1], A[i]) >= 0)sn--;
            s[sn++] = A[i];
        }
        int i = 0, j = 0;
        pll ans1, ans2;
        while (i < sn){
            if (mx < dis(s[i], s[j])){
                mx = dis(s[i], s[j]);
                ans1 = s[i], ans2 = s[j];
            }
            if ((s[(i + 1) % sn].first - s[i].first) * (s[(j + 1) % sn].second - s[j].second) >= (s[(i + 1) % sn].second - s[i].second) * (s[(j + 1) % sn].first - s[j].first)) i++;
            else j = (j + 1) % N;
        }
        printf("%lld %lld %lld %lld\n", ans1.first, ans1.second, ans2.first, ans2.second);
    }
    return 0;
}