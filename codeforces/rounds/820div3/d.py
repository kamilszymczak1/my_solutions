for _ in range(int(input())):
    n = int(input())
    
    pos, neg = [], []
    
    x = list(map(int, input().split()))
    y = list(map(int, input().split()))
    
    for i in range(n):
        if y[i] - x[i] < 0:
            neg.append(x[i] - y[i])
        else:
            pos.append(y[i] - x[i])
            
    pos.sort()
    neg.sort()
    
    i = len(pos) - 1
    j = len(neg) - 1
    answer = 0
    while i >= 0:
        while j >= 0 and neg[j] > pos[i]:
            j -= 1
        
        if j >= 0:
            i -= 1
            j -= 1
            answer += 1
        elif i >= 1:
            i -= 2
            answer += 1
        else:
            i = -1
    
    print(answer)
