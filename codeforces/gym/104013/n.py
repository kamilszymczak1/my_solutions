fac = [1]
while len(fac) < 120:
    fac.append(fac[-1] * len(fac))
    
def binom(n, k):
    return fac[n] // (fac[k] * fac[n - k])
    
def symmetric(n, k):
    if n % 2 == 0 and k % 2 == 1:
        return 0
    return binom(n // 2, k // 2)
    
n, k = map(int, input().split())
    
answer = 0
for x in range(k + 1):
    
    if x <= n and k - x <= n:
        if 2 * x == k:
            answer += binom(n, x) + symmetric(n, x)
        else:
            answer += (binom(n, x) + symmetric(n, x)) // 2
    
print(answer)
