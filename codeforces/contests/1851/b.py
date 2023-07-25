import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = sorted(a)
    print("No" if any([a[i] % 2 != b[i] % 2 for i in range(n)]) else "Yes")
    
