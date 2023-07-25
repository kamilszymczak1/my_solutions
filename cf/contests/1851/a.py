import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n, m, k, H = map(int, input().split())
    result = 0
    for h in list(map(int, input().split())):
        dh = abs(H - h)
        if dh % k == 0 and dh // k < m and dh != 0:
            result += 1
    print(result)
