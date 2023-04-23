from random import randint

n = 300000
q = 300000
mod = 1000000007
print(n, q, mod)

for i in range(n):
    print(randint(0, mod - 1), end = " ")
print("")
for i in range(n):
    print(randint(0, mod - 1), end = " ")
print("")

for i in range(q):
    print("A", 1, n)
