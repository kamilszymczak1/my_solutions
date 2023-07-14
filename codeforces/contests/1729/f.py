for _ in range(int(input())):
    s = input()
    w, m = map(int, input().split())
    n = len(s)
    
    M = 9
    
    where = [[] for i in range(M)]
    
    my_sum = 0
    for i in range(w):
        my_sum += int(s[i])
        
    where[my_sum % 9].append(0)
    for i in range(n - w):
        my_sum -= int(s[i])
        my_sum += int(s[i + w])
        if len(where[my_sum % 9]) < 2:
            where[my_sum % 9].append(i + 1)
    
    p = [0]
    for c in s:
        p.append(p[-1] + int(c))
        
    for __ in range(m):
        l, r, k = map(int, input().split())
        c = p[r] - p[l - 1]
        
        answer = (n, n)
        for i in range(M):
            j = (k - i * c % M + M) % M
            
            if i == j:
                if len(where[i]) > 1:
                    answer = min(answer, (where[i][0], where[i][1]))
            else:
                if len(where[i]) > 0 and len(where[j]) > 0:
                    answer = min(answer, (where[i][0], where[j][0]))
                    
        if answer == (n, n):
            print("-1 -1")
        else:
            print(answer[0] + 1, answer[1] + 1)
