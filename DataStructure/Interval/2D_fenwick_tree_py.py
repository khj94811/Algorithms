import sys
read = lambda : sys.stdin.readline().strip()
def update(r, c, diff) :
    tc = c
    while r <= N :
        c = tc
        while c <= N :
            BIT[r][c] += diff
            c += c & -c
        r += r & -r
def query(r, c) :
    ret = 0
    tc = c
    while 1 <= r :
        c = tc
        while 1 <= c :
            ret += BIT[r][c]
            c -= c & -c
        r -= r & -r
    return ret
def sum(r1, c1, r2, c2) :
    return query(r2, c2) - query(r1 - 1, c2) - query(r2, c1 - 1) + query(r1 - 1, c1 - 1)
N, M = map(int, read().split())
A = [[0]]
for i in range(N) :
    A.append([0, *map(int, read().split())])
BIT = [[0] * (2 * N) for i in range(2 * N)]
for i in range(1, N + 1) :
    for j in range(1, N + 1) :
        update(i, j, A[i][j])
for tt in range(M) :
    B = [*map(int, read().split())]
    if B[0] == 1 :
        r1 = B[1]
        c1 = B[2]
        r2 = B[3]
        c2 = B[4]
        if r1 > r2 :
            r1, r2 = r2, r1
        if c1 > c2 :
            c1, c2 = c2, c1
        print(sum(r1, c1, r2, c2))
    else :
        r = B[1]
        c = B[2]
        val = B[3]
        update(r, c, -A[r][c] + val)
        A[r][c] = val
