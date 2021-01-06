#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, sum[11], cant[11];
string S[55];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);  cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> S[i];
        for (ll j = S[i].length() - 1, k = 1; j >= 0; j--, k *= 10) {
            sum[S[i][j] - 'A'] += k;
        }
        cant[S[i][0] - 'A'] = 1;
    }
    ll ans = 0;
    for (int i = 0; i < 10; i++) {
        ll mn = 1e14, mnidx = -1;
        for (int j = 0; j < 10; j++) {
            if (!cant[j] && sum[j] < mn) {
                mn = sum[j];
                mnidx = j;
            }
        }
        if (!i) {
            for (int j = 0; j < 10; j++)    cant[j] = 0;
        }
        ans += 1LL * i * sum[mnidx];
        cant[mnidx] = 1;
    }
    cout << ans << '\n';
    return 0;
}