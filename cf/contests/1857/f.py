import sys
input = sys.stdin.readline
import math

def perfect_square(x):
    y = int(round(math.sqrt(x)))
    return y * y == x

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    count = dict()
    for x in a:
        if x in count.keys():
            count[x] += 1
        else:
            count[x] = 1
    
    for __ in range(int(input())):
        x, y = map(int, input().split())
        
        if x * x - 4 * y < 0 or not perfect_square(x * x - 4 * y):
            print("0", end = " ")
        else:
            d = int(round(math.sqrt(x * x - 4 * y)))
            
            if d == 0:
                c = count[x // 2]
                print(c * (c - 1) // 2, end = " ")
            else:
                print(count[(x - d) / 2] * count[(x + d) / 2], end = " ")
        
    print("")
