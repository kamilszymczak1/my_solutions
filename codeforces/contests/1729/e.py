for i in range(2, 26):
print("?", 1, i, flush = True)
d1 = int(input())
print("?", i, 1, flush = True)
d2 = int(input())

if d1 == -1:
    print("!", i - 1, flush = True)
    break

if d1 != d2:
    print("!", d1 + d2, flush = True)
    break
