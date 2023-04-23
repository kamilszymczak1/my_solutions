for _ in range(int(input())):
    n = int(input())
    
    a = [0] + list(map(int, input().split()))
    
    p = [0] * (n + 1)

    answer = 0
    for i in range(1, n + 1):
        
        if a[i] < i and a[i] != 0:
            answer += p[a[i] - 1]
        
        p[i] = p[i - 1]
        if a[i] < i:
            p[i] += 1
    
    print(answer)
