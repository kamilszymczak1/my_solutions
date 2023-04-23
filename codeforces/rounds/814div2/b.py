for _ in range(int(input())):
    n, k = map(int, input().split())
    if k % 4 == 0:
        print("NO")
        continue
    
    print("YES")
    for i in range(n // 2):
        a, b = i * 2 + 1, i * 2 + 2
        
        if (a + k) * b % 4 == 0:
            print(a, b)
        else:
            print(b, a)
