from random import randint

n = randint(2, 50)
print(n)
a = [0] * (2 * n)
b = [0] * (2 * n)

k = min(2 * n, 9)

for i in range(k):
    x = randint(0, 2 * n - 1)
    while a[x] == 1:
        x = randint(0, 2 * n - 1)
    a[x] = 1
    x = randint(0, 2 * n - 1)
    while b[x] == 1:
        x = randint(0, 2 * n - 1)
    b[x] = 1
    
for i in range(n):
    print(a[i], end = " ")
print("")
for i in range(n):
    print(a[i + n], end = " ")
print("")
for i in range(n):
    print(b[i], end = " ")
print("")
for i in range(n):
    print(b[i + n], end = " ")
print("")
