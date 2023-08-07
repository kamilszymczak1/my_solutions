import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    b = list(sorted(list(map(int, input().split()))))
    for i in range(n - 1):
        print(b[i * n - i - i * (i - 1) // 2], end = " ")
    print(b[-1])
