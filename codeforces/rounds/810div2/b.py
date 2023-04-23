for _ in range(int(input())):
    
    n, m = map(int, input().split())
    
    a = list(map(int, input().split()))
    
    deg = [0] * n
    
    e = []
    
    for i in range(m):
        x, y = map(int, input().split())
        deg[x - 1] += 1
        deg[y - 1] += 1
        e.append((x - 1, y - 1))
        
    if m % 2 == 0:
        print(0)
    else:
        ans = 1 << 30
        for i in range(n):
            if deg[i] % 2 == 1:
                ans = min(ans, a[i])
        
        for (x, y) in e:
            if deg[x] % 2 == deg[y] % 2:
                ans = min(ans, a[y] + a[x])
        
        print(ans)
