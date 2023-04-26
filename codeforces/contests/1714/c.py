dp = [1 << 30] * 46
dp[0] = 0
for digit in range(1, 10):
    new_dp = dp.copy()
    for i in range(46):
        if i + digit <= 45:
            new_dp[i + digit] = min(new_dp[i + digit], dp[i] * 10 + digit)
    
    dp = new_dp.copy()
    
for _ in range(int(input())):
    print(dp[int(input())])
