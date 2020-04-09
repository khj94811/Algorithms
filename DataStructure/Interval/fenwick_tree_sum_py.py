import sys
read = lambda : sys.stdin.readline().strip()
def update(pos, val) :
    while pos <= N :
        BIT[pos] += val
        pos += pos & -pos
def query(pos) :
    ret = 0
    while pos >= 1 :
        ret += BIT[pos]
        pos -= pos & -pos
    return ret
def sum(l, r) :
    return query(r) - query(l - 1)
N, M, K = map(int, read().split())
BIT = [0] * (3 * N)
for i in range(1, N + 1) :
    update(i, int(read()))
for i in range(M + K) :
    c, l, r = map(int, read().split())
    if c == 1 :
        val = sum(l, l)
        update(l, -val + r)
    else :
        print(sum(l, r))