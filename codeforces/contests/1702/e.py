or _ in range(int(input())):
n = int(input())

where = [[] for i in range(n)]

for i in range(n):
    a, b = map(int, input().split())
    where[a - 1].append(i)
    where[b - 1].append(i)

answer = True

adj = [[] for i in range(n)]

for i in range(n):
    if len(where[i]) != 2:
        answer = False
    else:
        a, b = where[i]
        adj[a].append(b)
        adj[b].append(a)
        
color = [-1] * n

for i in range(n):
    if color[i] == -1:
        color[i] = 0
        stack = [i]
        while len(stack) > 0:
            x = stack[-1]
            stack.pop()
            for y in adj[x]:
                if color[y] == color[x]:
                    answer = False
                
                if color[y] == -1:
                    color[y] = 1 - color[x]
                    stack.append(y)

print("YES" if answer else "NO")
