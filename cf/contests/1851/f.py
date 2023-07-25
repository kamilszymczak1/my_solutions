import sys
input = sys.stdin.readline

def check(target, a):
    a = sorted([x & target for x in a])
    for i in range(len(a) - 1):
        if a[i] == a[i + 1]:
            return True
    return False

def get_indices(target, a):
    a = sorted([(a[i] & target, i + 1) for i in range(len(a))])
    for i in range(len(a) - 1):
        if a[i][0] == a[i + 1][0]:
            return [a[i][1], a[i + 1][1], a[i][0] ^ target]
    return []

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    
    result = 0
    for i in range(k):
        result ^= 1 << (k - i - 1)
        if not check(result, a):
            result ^= 1 << (k - i - 1)
    print(*get_indices(result, a))
