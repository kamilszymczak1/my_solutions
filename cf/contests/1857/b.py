import sys
input = sys.stdin.readline
for _ in range(int(input())):
    s = list(reversed('0' + input().strip()))
    d = [int(x) for x in s]
    t = len(s)
    i = 1
    r = 0
    while i < t:
        if d[i - 1] >= 5:
            d[i - 1] = 0
            j = i
            while d[j] == 9:
                d[j] = 0
                j += 1
            r = i
            d[j] += 1
            i = j
        i += 1
        
    for i in range(r):
        d[i] = 0
    
    d = list(reversed(d))
    d = [str(x) for x in d]
    if d[0] == "0":
        print("".join(d[1:]))
    else:
        print("".join(d))
        
        
