import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    xs = [(x, index) for index, x in enumerate(map(int, input().split()))]
    xs.sort()
    value = sum([x for x, index in xs]) - xs[0][0] * n  + n
    anss = [0] * n
    anss[xs[0][1]] = value
    for i in range(1, n):
        value += (xs[i][0] - xs[i - 1][0]) * (2 * i - n)
        anss[xs[i][1]] = value
    print(*anss)




        
