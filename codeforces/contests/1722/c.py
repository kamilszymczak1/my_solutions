for _ in range(int(input())):
    
    n = int(input())
    
    A = []
    
    for player in range(3):
        
        S = list(input().split())
        
        for s in S:
            A.append((s, player))
    
    A.sort()
    
    score = [0] * 3
    
    i = 0
    while i < 3 * n:
        j = i
        while j < 3 * n and A[i][0] == A[j][0]:
            j += 1
            
        l = j - i
        
        if l == 1:
            score[A[i][1]] += 3
        
        if l == 2:
            score[A[i][1 + 0]] += 1
            score[A[i + 1][1]] += 1
            
        i = j
    
    print(*score)
