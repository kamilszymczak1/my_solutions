from math import gcd
n = int(input())
nxt = [list(map(lambda x : int(x) - 1, input().split()))[1::] for i in range(n)]
prv = [[] for i in range(n)]
for x in range(n):
    for y in nxt[x]:
        prv[y].append(x)
dp_t, dp_cnt = [1] * n, [0] * n
dp_t[0] = max(1, len(nxt[0]))
dp_cnt[0] = dp_t[0]
for x in range(1, n):
    dp_t[x] = dp_t[x - 1]
    suitcases_t = 0
    for y in prv[x]:
        suitcases_t += dp_cnt[y] * dp_t[x - 1] // (dp_t[y] * len(nxt[y]))
    if suitcases_t > 0 and len(nxt[x]) > 0:
        if len(nxt[x]) == 0:
            dp_cnt[x] = suitcases_t
        else:  
            k = len(nxt[x]) // gcd(suitcases_t, len(nxt[x]))
            dp_t[x] *= k
            dp_cnt[x] = suitcases_t * k
print(dp_t[n - 1])
