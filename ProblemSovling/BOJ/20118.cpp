#include <bits/stdc++.h>
using namespace std;
int N, M, A[1005][1005];

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &A[i][j]);
        }
    }
    vector<pair<int, int>> vt, ans;
    for (int i = 0; i < N; i++) vt.push_back({i, 0});
    for (int i = 1; i < M; i++) vt.push_back({N - 1, i});
    for (int i = 1; i < vt.size(); i += 2) {
        for (int j = 0; j < 2; j++) {
            ans.push_back({vt[i - 1].first, vt[i - 1].second});
            ans.push_back({vt[i].first, vt[i].second});
        }
    }
    if (vt.size() & 1) {
        for (int j = 0; j < 2; j++) {
            ans.push_back({N - 2, M - 1});
            ans.push_back({N - 1, M - 1});
        }
    }
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }
    return 0;
}