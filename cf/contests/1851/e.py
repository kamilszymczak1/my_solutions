import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n, k = map(int, input().split())
    c = list(map(int, input().split()))
    for p in list(map(int, input().split())):
        c[p - 1] = 0
        
    ou_adj = [[] for i in range(n)]
    in_adj = [[] for i in range(n)]
    for i in range(n):
        for x in list(map(int, input().split()))[1:]:
            ou_adj[x - 1].append(i)
            in_adj[i].append(x - 1)
            
    visited = [False] * n
    topo_order = []
    
    nei_id = [0] * n
    
    for i in range(n):
        if not visited[i]:
            st = [i]
            visited[i] = True
            while len(st) > 0:
                x = st[-1]
                
                while nei_id[x] < len(ou_adj[x]):
                    if not visited[ou_adj[x][nei_id[x]]]:
                        st.append(ou_adj[x][nei_id[x]])
                        visited[ou_adj[x][nei_id[x]]] = True
                        break
                    nei_id[x] += 1
                else:
                    topo_order.append(x)
                    st.pop()
            
    topo_order.reverse()
    
    for x in topo_order:
        if len(in_adj[x]) != 0:
            c[x] = min(c[x], sum([c[i] for i in in_adj[x]]))
        
    print(*c)
            
        
