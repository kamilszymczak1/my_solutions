class segment_tree:
    def __init__(self, n):
        self.leaf_count = 1
        while self.leaf_count < n:
            self.leaf_count *= 2
        self.values = [0] * (self.leaf_count * 2)
        
    def add(self, x, value):
        x += self.leaf_count
        while x > 0:
            self.values[x] += value
            x >>= 1
            
    def get_sum(self, a, b):
        a += self.leaf_count
        b += self.leaf_count
        result = self.values[a] + (self.values[b] if a != b else 0)
        while (a >> 1) != (b >> 1):
            if (a & 1) == 0:
                result += self.values[a + 1]
            if (b & 1) == 1:
                result += self.values[b - 1]
            a >>= 1
            b >>= 1
        return result
    
for _ in range(int(input())):
    
    n, q = map(int, input().split())
    
    events = []
    
    for i in range(n):
        x, y = map(int, input().split())
        events.append((x, 0, y, 0))
        
    for i in range(1, q + 1):
        x1, y1, x2, y2 = map(int, input().split())
        if y1 + 1 <= y2 - 1 and x1 + 1 <= x2 - 1:
            events.append((x2 - 1, +i, y1 + 1, y2 - 1))
            events.append((x1 + 1, -i, y1 + 1, y2 - 1))
        
        
    events.sort()
    
    answers = [0] * q
    
    t = segment_tree(1024)
    
    for e in events:
        
        if e[1] == 0:
            t.add(e[2], e[0] * e[2])
        else:
            my_id = abs(e[1]) - 1
            s = t.get_sum(e[2], e[3])
            answers[my_id] += s if e[1] > 0 else -s
    
    for x in answers:
        print(x)
