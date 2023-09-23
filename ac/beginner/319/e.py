n, x, y = map(int, input().split())

k = 840

d = [[i + x for i in range(k)], [0] * k]


for s in range(n - 1):
    p, t = map(int, input().split())
    
    for i in range(k):
        d[(s & 1) ^ 1][i] = d[s & 1][i] + (p - d[s & 1][i] % p) % p + t
    
q = int(input())
for _ in range(q):
    a = int(input())
    print(k * (a // k) + d[(n & 1) ^ 1][a % k] + y)
