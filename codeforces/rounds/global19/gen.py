from random import randint

n = randint(3, 5)
print(n)
for i in range(n):
    print(randint(1, 5), end = " ")
print("")
for i in range(n - 1):
    print(i + 2, randint(1, i + 1))
