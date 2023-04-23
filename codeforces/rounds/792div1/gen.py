from random import randint

t = 2000
print(t)
for _ in range(t):
    n = randint(1, 10)
    k = randint(1, n)
    print(n, k)
    for i in range(n):
        print(randint(0, 10), end = " ")
    print("")
