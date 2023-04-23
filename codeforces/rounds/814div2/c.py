for _ in range(int(input())):
    n, q = map(int, input().split())
    
    a = list(map(int, input().split()))
    a = list(map(lambda x : x - 1, a))

    queries = []
    for i in range(q):
        x, y = map(int, input().split())
        queries.append((y, a[x - 1], i))
        
    won = [0] * n
        
    queries.sort()
    
    answer = [0] * q
    k = 0
    for t in range(n):
        while k < q and queries[k][0] <= t:
            answer[queries[k][2]] = won[queries[k][1]]
            k += 1
        
        nxt = t + 1 if t + 1 < n else t + 1 - n
        if a[t] > a[nxt]:
            won[a[t]] += 1
            a[t], a[nxt] = a[nxt], a[t]
        else:
            won[a[nxt]] += 1
    
    while k < q:
        if  queries[k][1] == n - 1:
            answer[queries[k][2]] = won[queries[k][1]] + queries[k][0] - n
        else:
            answer[queries[k][2]] = won[queries[k][1]]
        k += 1
    [print(x) for x in answer]
    
    
