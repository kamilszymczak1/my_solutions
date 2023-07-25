import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n = int(input())
    p = list(map(int, input().split()))
    a = [p[0]] + [p[i] - p[i - 1] for i in range(1, n - 1)]
    answer = "Yes"
    if p[n - 2] * 2 != n * (n + 1):
        p.append(n * (n + 1) // 2)
        a.append(p[n - 1] - p[n - 2])
        a.sort()
        for i in range(n):
            if a[i] != i + 1:
                answer = "No"
    else:
        a.sort()
        i = 0
        while i < len(a) and a[i] == i + 1:
            i += 1
        if i == len(a):
            answer = "No"
        else:
            missing = i + 1
            j = n - 2
            while j >= 0 and a[j] == j + 2:
                j -= 1
            
            if j == -1:
                answer = "No"
            else:
                a.append(a[j] - missing)
                a[j] = missing
            a.sort()
            for i in range(n):
                if a[i] != i + 1:
                    answer = "No"
        
    print(answer)
