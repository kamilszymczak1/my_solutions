import sys
input = sys.stdin.readline

mod = 998244353

def mod_pow(x, exp):
    result = 1
    while exp > 0:
        if exp & 1:
            result = result * x % mod
        x = x * x % mod
        exp >>= 1
    return result

class dsu:
    def __init__(self, n):
        self.f = [x for x in range(n)]
        self.s = [1 for x in range(n)]
        
    def comp_size(self, x):
        return self.s[x]
    
    def find(self, x):
        y = x
        while self.f[y] != y:
            y = self.f[y]
        while x != y:
            self.f[x], x = y, self.f[x]
        return self.f[x]
    
    def union(self, x, y):
        x = self.find(x)
        y = self.find(y)
        if x != y:
            if self.s[x] < self.s[y]:
                x, y = y, x
            self.s[x] += self.s[y]
            self.f[y] = x

for _ in range(int(input())):
    n, s = map(int, input().split())
    edges = []
    for i in range(n - 1):
        a, b, w = map(int, input().split())
        edges.append((w, a - 1, b - 1))
        
    edges.sort()
    
    my_dsu = dsu(n)
    
    answer = 1
    for w, a, b in edges:
        a = my_dsu.find(a)
        b = my_dsu.find(b)
        a_s, b_s = my_dsu.comp_size(a), my_dsu.comp_size(b)
        
        answer = answer * mod_pow(s + 1 - w, a_s * b_s - 1) % mod
        
        my_dsu.union(a, b)
    
    print(answer)
    
    
    
