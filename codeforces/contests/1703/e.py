for _ in range(int(input())):
    
    n = int(input())
    a = [input() for i in range(n)]
    
    answer = 0
    
    for i in range((n + 1) // 2):
        for j in range(n // 2):
            count = int(a[i][j]) + int(a[n - j - 1][i]) + int(a[j][n - i - 1]) + int(a[n - i - 1][n - j - 1])
            answer += min(count, 4 - count)
            
    print(answer)
