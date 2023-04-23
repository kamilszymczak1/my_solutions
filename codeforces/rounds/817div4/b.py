for _ in range(int(input())):
    
    n = int(input())
    s1 = input()
    s2 = input()
    
    answer = True
    
    for i in range(n):
        
        if s1[i] != s2[i]:
            
            a = [s1[i], s2[i]]
            a.sort()
            
            if a != ['B', 'G']:
                answer = False
    
    print("YES" if answer else "NO")
