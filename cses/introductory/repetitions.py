s = input()
current, best = 1, 1
for i in range(1, len(s)):
    current = current + 1 if s[i] == s[i - 1] else 1
    best = max(best, current)
print(best)
