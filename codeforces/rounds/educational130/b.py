n, q = map(int, input().split())

a = [0] + list(map(int, input().split()))
a.sort()

for i in range(n):
    a[i + 1] += a[i]
    
for _ in range(q):
    x, y = map(int, input().split())
    print(a[n - x + y] - a[n - x])
