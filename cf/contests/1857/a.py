import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    if sum(a) % 2 == 0 and n > 1:
        print("YES")
    else:
        print("NO")
