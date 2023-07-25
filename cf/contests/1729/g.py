inf = 1 << 30
mod = 1000000007

for _ in range(int(input())):
s = input()
t = input()
n, m = len(s), len(t)

ind = [-inf]

for i in range(n - m + 1):
    if s[i:i+m] == t:
        ind.append(i)
        
dp = [1 << 20] * len(ind)

ways = [0] * len(ind)

ways[0] = 1
dp[0] = 0

l, r = 0, 0

for t_pos in ind:
    while l < len(ind) and ind[l] <= t_pos - m:
        l += 1
        
    while r < len(ind) - 1 and ind[r + 1] < t_pos + m:
        r += 1
        
    k = l - 1
    while k < r and ind[k] < t_pos:
        dp[r] = min(dp[r], dp[k] + 1)
        k += 1
    
    k = l - 1
    while k < r and ind[k] < t_pos:
        if dp[r] == dp[k] + 1:
            ways[r] += ways[k]
            if ways[r] >= mod:
                ways[r] -= mod
        k += 1
    

print(dp[-1], ways[-1])
