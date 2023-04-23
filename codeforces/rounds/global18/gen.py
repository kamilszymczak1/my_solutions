from random import randint
print(1)
n = 100000
print(n)
a = [0] * n
b = [0] * n
for i in range(randint(1, 1000)):
    a[randint(0, n - 1)] = 1
    b[randint(0, n - 1)] = 1
for i in range(n):
    print(a[i], end = "")
print("")
for i in range(n):
    print(b[i], end = "")
print("")
