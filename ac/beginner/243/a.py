from random import randint

T = 100000
cnt = 0
for _ in range(T):
    a = []
    for i in range(2):
        a.append(randint(1, 3))
    if a[0] != a[1]:
        cnt += 1
print(cnt / T)
