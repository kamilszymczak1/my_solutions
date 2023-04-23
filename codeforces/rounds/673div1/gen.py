from random import randint
from random import shuffle

n = randint(2, 5)
m = randint(1, min(5, int(n * (n - 1) / 2)))
q = randint(1, 5)

p = [i + 1 for i in range(n)]

print(n, m, q)
print(*p)
edges = []
for i in range(m):
    a = randint(1, n)
    b = randint(1, n)
    if a > b:
        a, b = b, a
    while a == b or (a, b) in edges:
        a = randint(1, n)
        b = randint(1, n)
        if a > b:
            a, b = b, a
    edges.append((a, b))
    print(a, b)
    
erased = [False] * m
erasedCnt = 0
for i in range(q):
    t = randint(1, 2)
    if erasedCnt == m:
        t = 1
    if t == 1:
        print(t, randint(1, n))
    else:
        k = randint(0, m - 1)
        while erased[k]:
            k = randint(0, m - 1)
        erased[k] = True
        erasedCnt += 1
        print(t, k + 1)
