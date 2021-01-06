#include <bits/stdc++.h>
using namespace std;
int N, M;
int main() {
    scanf("%d %d", &N, &M);
    if (M <= 2) {
        puts("NEWBIE!");
    }
    else if (M <= N) {
        puts("OLDBIE!");
    }
    else {
        puts("TLE!");
    }
    return 0;
}