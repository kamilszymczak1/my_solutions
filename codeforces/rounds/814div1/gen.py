from random import randint

t = 1
print(t)
for i in range(t):
    n = randint(2, 10)
    print(n, 0)
    print(*[randint(1, 3) for i in range(n)])
