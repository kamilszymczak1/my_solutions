import sys
from collections import Counter
import math

input = sys.stdin.readline

def perfect_square(x):
    y = int(math.sqrt(x))
    return y * y == x

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    a.sort()
    
    def count_in_a(x):
        l, r = 0, n - 1
        while l < r:
            m = (l + r) >> 1
            if a[m] < x:
                l = m + 1
            else:
                r = m
        if l == n or a[l] != x:
            return 0
        p, q = l, n
        while p < q:
            m = (p + q) >> 1
            if a[m] <= x:
                p = m + 1
            else:
                q = m
        return p - l
            
    
    
    for __ in range(int(input())):
        x, y = map(int, input().split())
        
        if x * x - 4 * y < 0 or not perfect_square(x * x - 4 * y):
            print("0", end = " ")
        else:
            d = int(math.sqrt(x * x - 4 * y))
            
            if d == 0:
                c = count_in_a(x // 2)
                print(c * (c - 1) // 2, end = " ")
            else:
                print(count_in_a((x - d) // 2) * count_in_a((x + d) // 2), end = " ")
        
    print("")
