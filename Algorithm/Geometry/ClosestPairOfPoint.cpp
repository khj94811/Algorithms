#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int MAX = 5e5 + 5;
int N;
pii A[MAX];

inline int getDist(pii a, pii b){
    int xdiff = b.first - a.first;
    int ydiff = b.second - a.second;
    return xdiff * xdiff + ydiff * ydiff;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d %d", &A[i].first, &A[i].second);
    }
    sort(A, A + N);
    int idx = 0, ans = 2e9;
    set<pii> st;
    for(int i = 0; i < N; i++){
        while(idx < i){
            int xdiff = A[i].first - A[idx].first;
            if(xdiff * xdiff > ans){
                pii er = {A[idx].second, A[idx].first};
                st.erase(er);
                idx++;
            }
            else break;
        }
        int dis = (int)sqrt((double)ans) + 1;
        auto le = st.lower_bound(make_pair(A[i].second - dis, -1e9));
        auto ri = st.upper_bound(make_pair(A[i].second + dis, 1e9));
        while(le != ri){
            pii p = *le;   swap(p.first, p.second);
            int ndis = getDist(p, A[i]);
            ans = min(ans, ndis);
            le++;
        }
        pii ins = {A[i].second, A[i].first};
        st.insert(ins);
    }
    printf("%d\n", ans);
    return 0;
}
