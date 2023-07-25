for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(min([max(0, (a[i] - a[i - 1] + 2) // 2) for i in range(1, n)]))
