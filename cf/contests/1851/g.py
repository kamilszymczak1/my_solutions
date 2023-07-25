import sys
input = sys.stdin.readline

class dsu:
    def __init__ (self, n):
        self.f = [i for i in range(n)]
    def find(self, x):
        st = [x]
        while self.f[st[-1]] != st[-1]:
            st.append(self.f[st[-1]])
        for x in st:
            self.f[x] = st[-1]
        return st[-1]
    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)
        self.f[x] = y
        
class query:
    def __init__(self, a, b, e, ind):
        self.a = a
        self.b = b
        self.e = e
        self.ind = ind

for _ in range(int(input())):
    n, m = map(int, input().split())
    h = list(map(int, input().split()))
    adj = [[] for i in range(n)]
    for i in range(m):
        u, v = map(int, input().split())
        adj[v - 1].append(u - 1)
        adj[u - 1].append(v - 1)
        
    q = int(input())
        
    queries = []
    for i in range(q):
        a, b, e = map(int, input().split())
        queries.append(query(a - 1, b - 1, h[a - 1] + e, i))
        
    queries.sort(key=lambda q : q.e)
    h_ord = sorted([(h[i], i) for i in range(n)])
    h_ind = 0
    
    my_dsu = dsu(n)
    
    answer = ["No"] * q
    
    for my_query in queries:
        while h_ind < n and h_ord[h_ind][0] <= my_query.e:
            x = h_ord[h_ind][1]
            for y in adj[x]:
                if h[y] <= my_query.e:
                    my_dsu.union(x, y)
            h_ind += 1
        
        if my_dsu.find(my_query.a) == my_dsu.find(my_query.b):
            answer[my_query.ind] = "Yes"
    
    for x in answer:
        print(x)
