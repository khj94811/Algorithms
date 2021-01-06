#include <bits/stdc++.h>
using namespace std;
int N, ans = 1;
int main() {
    scanf("%d", &N);
    for (int i = 0; i < 32; i++) {
        if (N & (1 << i))   ans = i + 1;
    }
    printf("%d\n", ans);
    return 0;
}