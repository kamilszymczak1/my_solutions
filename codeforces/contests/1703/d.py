from random import randint
    
def prime(x):
    i = 2
    while i * i <= x:
        if x % i == 0:
            return False
        i += 1
    return True
    
class HashTable:
    
    def get_hash(self, s):
        result = 0
        for c in s:
            result = (result * 29 + ord(c) - ord('a') + 1) % self.size
        return result
    
    def __init__(self, min_size):
        self.size = min_size
        while not prime(self.size):
            self.size += 1
        self.lists = [ [] for i in range(self.size) ]
        
    def insert(self, s):
        h = self.get_hash(s)
        for t in self.lists[h]:
            if t == s:
                return
        self.lists[h].append(s)
        
    def find(self, s):
        h = self.get_hash(s)
        for t in self.lists[h]:
            if t == s:
                return True
        return False
    
    
for _ in range(int(input())):
    n = int(input())
    h = HashTable(2 * n)
    S = [input() for i in range(n)]
    
    for s in S:
        h.insert(s)
    
    for s in S:
        answer = "0"
        for i in range(len(s) - 1):
            if h.find(s[0 : i + 1]) and h.find(s[i + 1 : len(s)]):
                answer = "1"
        
        print(answer, end = "")
    print("")
