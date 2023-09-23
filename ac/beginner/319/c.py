import math

def next_permutation(a):
    
    n = len(a)
    
    i = n - 2
    while i >= 0 and a[i] >= a[i + 1]:
        i -= 1
    
    if i < 0:
        return False
    
    j = i + 1
    while j < n - 1 and a[j + 1] > a[i]:
        j += 1
    
    a[i], a[j] = a[j], a[i]
        
    a[i + 1:] = list(reversed(a[i + 1:]))
    
    return True


c = [list(map(int, input().split())) for i in range(3)] 

indices = [(i, j) for i in range(3) for j in range(3)]

count = 0

while True:
    
    cols = [[], [], []]
    rows = [[], [], []]
    dial = []
    diar = []
    
    for row, col in indices:
        cols[col].append(c[row][col])
        rows[row].append(c[row][col])
        if row == col:
            diar.append(c[row][col])
        if row + col == 2:
            dial.append(c[row][col])
            
    disappointed = False
    for l in (cols + rows + [dial, diar]):
        if l[0] == l[1] and l[1] != l[2]:
            disappointed = True
            
    if not disappointed:
        count += 1
    
    if not next_permutation(indices):
        break


print(count / math.prod([i + 1 for i in range(9)]))

