for _ in range(int(input())):
    
    n, m = map(int, input().split())

    visited = [ [True] * (m + 2) for i in range(n + 2) ]
    
    for i in range(1, n + 1):
        s = input()
        for j in range(1, m + 1):
            visited[i][j] = True if s[j - 1] == '.' else False
            
    
    moves = [ (0, 1), (1, 1), (1, 0), (0, -1), (-1, 0), (-1, -1), (1, -1), (-1, 1) ]
    
    answer = True
    
    for i in range(1, n + 1):
        for j in range(1, m + 1):
            
            if not visited[i][j]:
                
                visited[i][j] = True
                q = [(i, j)]
                k = 0
                while k < len(q):
                    (x, y) = q[k]
                    
                    for (dx, dy) in moves:
                        
                        new_x, new_y = x + dx, y + dy
                        
                        if not visited[new_x][new_y]:
                            visited[new_x][new_y] = True
                            q.append((new_x, new_y))
                    k += 1
                        
                        
                if len(q) != 3:
                    answer = False
                else:
                    
                    q.sort()
                    x, y = q[0]
                    
                    ok = False
                    
                    if q[1] == (x + 1, y - 1) and q[2] == (x + 1, y):
                        ok = True
                        
                    if q[1] == (x + 1, y) and q[2] == (x + 1, y + 1):
                        ok = True
                        
                    if q[1] == (x, y + 1) and q[2] == (x + 1, y + 1):
                        ok = True
                    
                    if q[1] == (x, y + 1) and q[2] == (x + 1, y):
                        ok = True
                    
                    if not ok:
                        answer = False
            
        
    print("YES" if answer else "NO")
                    
                            
