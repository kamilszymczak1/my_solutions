from random import randint

n, q = 300, randint(1, 1)
print(n, q)
x, w = [], []
for i in range(n):
    a = randint(-n, n)
    while a in x:
        a = randint(-n, n)
    x.append(a)
    w.append(randint(1, n))
    
x.sort()
for i in range(n):
    print(x[i], w[i])

print(1, n)
