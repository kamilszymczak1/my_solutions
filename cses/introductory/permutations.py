n = int(input())

if 2 <= n <= 3:
    print("NO SOLUTION")
else:
    print(*[1 + i // 2 + (n // 2 if i % 2 == 0 else 0) for i in range(n)])
