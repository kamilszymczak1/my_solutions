for _ in range(int(input())):
    n, m = map(int, input().split())
    s = sum(list(map(int, input().split())))
    print(max(0, s - m))
