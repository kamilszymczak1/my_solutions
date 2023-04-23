from random import randint

n = randint(1, 5)
print(n, n - 1)
print(1, end = " ")
for i in range(n - 1):
    print(randint(1, 2), end = " ")
print("")
    
for i in range(n - 1):
    print(randint(1, i + 1), i + 2)
