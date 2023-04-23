mod = 1000000009
b = 7

x = 1
m = set()

for i in range(300000):
    x = x * b % mod
    if x in m:
        print("Wrong")
    m.add(x)
