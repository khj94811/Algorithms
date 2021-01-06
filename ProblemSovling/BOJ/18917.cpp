#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int M;
ll x, s;

int main() {
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        int c;  scanf("%d", &c);
        if (c == 1) {
            ll d; scanf("%lld", &d);
            x ^= d;
            s += d;
        }
        else if (c == 2) {
            ll d; scanf("%lld", &d);
            x ^= d;
            s -= d;
        }
        else if (c == 3) {
            printf("%lld\n", s);
        }
        else {
            printf("%lld\n", x);
        }
    }
    return 0;
}