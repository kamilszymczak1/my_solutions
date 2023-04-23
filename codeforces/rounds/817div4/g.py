for _ in range(int(input())):
    
    n = int(input())
    
    a = []
    
    if n % 4 != 2:
        for i in range(20, n // 4 + 20):
            a += [0 + 4 * i, 2 + 4 * i, 1 + 4 * i, 3 + 4 * i]
            
        if n % 4 == 1:
            a += [0]
            
        if n % 4 == 3:
            a += [1, 3, 2]
    
    else:
        
        for i in range(20, (n - 6) // 4 + 20):
            a += [0 + 4 * i, 2 + 4 * i, 1 + 4 * i, 3 + 4 * i]
            
        a += [4, 1, 2, 12, 3, 8]
    
    print(*a)
