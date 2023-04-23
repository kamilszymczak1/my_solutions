MAX_KEY = 31
inf = 1 << 60

for _ in range(int(input())):
    
    n, k = map(int, input().split())
    
    a = list(map(int, input().split()))
    
    dp = [0] * MAX_KEY
    
    for i in range(n):
        new_dp = [-inf] * MAX_KEY
        for j in range(MAX_KEY):
            if j == MAX_KEY - 1:
                new_dp[j] = max(new_dp[j], dp[j])
            new_dp[j] = max(new_dp[j], dp[j] + (a[i] >> j) - k)
            if j + 1 < MAX_KEY:
                new_dp[j + 1] = max(new_dp[j + 1], dp[j] + (a[i] >> (j + 1)))
        dp = new_dp
        
    print(max(dp))
