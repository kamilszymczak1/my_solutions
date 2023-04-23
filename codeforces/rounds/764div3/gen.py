from random import randint
t = 10000
print(t)
for _ in range(t):
    n = randint(1, 50)
    print(n)
    for i in range(n):
        print(randint(1, n))
