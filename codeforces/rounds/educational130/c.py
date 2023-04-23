for _ in range(int(input())):
    
    n = int(input())
    s = input()
    t = input()
    
    nxt = [0] * 3
    
    for j in range(3):
        while nxt[j] < n and ord(s[nxt[j]]) - ord('a') != j:
            nxt[j] += 1
    
    answer = True
    for i in range(n):
        
        if t[i] == 'a':
            if nxt[0] > nxt[1] or nxt[0] > nxt[2] or nxt[0] >= n:
                answer = False
            nxt[0] += 1
            
        elif t[i] == 'b':
            if nxt[1] > nxt[2] or nxt[1] >= n:
                answer = False
            nxt[1] += 1    
            
        elif t[i] == 'c':
            if nxt[2] > nxt[0] or nxt[2] >= n:
                answer = False
            nxt[2] += 1
            
        for j in range(3):
            while nxt[j] < n and ord(s[nxt[j]]) - ord('a') != j:
                nxt[j] += 1
                
    print("YES") if answer else print("NO")
            
