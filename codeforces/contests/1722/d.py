

for _ in range(int(input())):
    
    n = int(input())
    
    s = input()
    
    A = []
    
    current = 0
    
    for i in range(n):
        
        right = n - 1 - i
        left = i
        
        if s[i] == 'L':
            current += left
            A.append(right - left)
        else:
            current += right
            A.append(left - right)
            
            
    
    A.sort()
    
    for i in range(n):
        if A[n - i - 1] >= 0:
            current += A[n - i - 1]
        print(current, end = " ")
    print("")

