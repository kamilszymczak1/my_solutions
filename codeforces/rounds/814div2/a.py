for _ in range(int(input())):
    n, m = map(int, input().split())
    print("Tonya" if n % 2 == m % 2 else "Burenka")
