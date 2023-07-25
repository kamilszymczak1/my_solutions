for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    
    for i in range(n):
        k, s = input().split()
        for c in s:
            if c == 'D':
                a[i] = (a[i] + 1) % 10
            else:
                a[i] = (a[i] + 9) % 10
    
    print(*a)
