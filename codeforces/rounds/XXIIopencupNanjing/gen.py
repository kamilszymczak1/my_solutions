from random import randint

X = 6

t = 1
print(t)
h = randint(2, 3)
print(h)
k = randint(2, X)
n = randint(1, k - 1)
print(n)
P = []
for i in range(n):
    a = randint(1, X)
    b = randint(1, h - 1)
    while (a, b) in P:
        a = randint(1, X)
        b = randint(1, h - 1)
    print(a, b)
    P.append((a, b))
print(k - n)
for i in range(k - n):
    a = randint(1, X)
    b = randint(1, h - 1)
    while (a, b) in P:
        a = randint(1, X)
        b = randint(1, h - 1)
    print(a, b)
    P.append((a, b))
    
