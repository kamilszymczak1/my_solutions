from random import randint

n = randint(2, 20)
m = randint(1, n)
print(n, m)
print(*[randint(0, 1) for i in range(n)])
for i in range(n - 1):
    print(i + 2, randint(1, i + 1))
