/* 
    과거긴 하지만, 명우님 블로그에서 많은 부분을 참조했었습니다.
    https://blog.myungwoo.kr/57?category=517571
*/
#include <bits/stdc++.h>
using namespace std;
const int MAX = 4e4 + 15;
int N, M, SA[MAX], lcp[MAX], seg[2][4 * MAX];
char S[MAX];

bool comp(int i, int len, vector<int> &y){
    if(SA[i] + len <= N && SA[i + 1] + len <= N){
        if(y[SA[i]] == y[SA[i + 1]] && y[SA[i] + len] == y[SA[i + 1] + len]){
            return false;
        }
    }
    return true;
}

void SuffixArray(){
    int lim = 256;
    vector<int> cnt(max(N, lim) + 1, 0), x(N + 1, 0), y(N + 1, 0);
    for(int i = 1; i <= N; i++){
        x[i] = S[i];
        cnt[x[i]]++;
    }
    for(int i = 1; i <= lim; i++){
        cnt[i] += cnt[i - 1];
    }
    for(int i = N; i >= 1; i--)
        SA[cnt[x[i]]--] = i;
    int p = 1;
    for(int len = 1; p < N; len <<= 1, lim = p){
        p = 0;
        for(int i = N - len; ++i <= N;)  y[++p] = i;
        for(int i = 1; i <= N; i++){
            if(SA[i] > len){
                y[++p] = SA[i] - len;
            }
        }
        for(int i = 0; i <= lim; i++)
            cnt[i] = 0;
        for(int i = 1; i <= N; i++)
        cnt[x[y[i]]]++;
        for(int i = 1; i <= lim; i++)
        cnt[i] += cnt[i - 1];
        for(int i = N; i >= 1; i--){
            SA[cnt[x[y[i]]]--] = y[i];
        }
        swap(x, y);
        p = 1;
        x[SA[1]] = 1;
        for(int i = 1; i < N; i++){
            p += comp(i, len, y);
            x[SA[i + 1]] = p;
        }
    }
}
void getLCP(){
    vector<int> rank(N + 1, 0);
    for(int i = 1; i <= N; i++){
        rank[SA[i]] = i;
    }
    int i, j, k = 0;
    for(i = 1; i <= N; lcp[rank[i]] = k, i++){
        for(k > 0 ? k-- : 0, j = SA[rank[i] - 1];; k++){
            if(S[i + k] != S[j + k])    break;
        }
    }
}
