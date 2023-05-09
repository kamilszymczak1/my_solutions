n = int(input())

if n % 4 == 1 or n % 4 == 2:
    print("NO")
else:
    print("YES")
    if n % 4 == 0:
        print(n // 2)
        for i in range(n // 4):
            print(i * 4 + 1, i * 4 + 4, end = " ")
        print("\n", n // 2, sep = "")
        for i in range(n // 4):
            print(i * 4 + 2, i * 4 + 3, end = " ")
        print("")
    else:
       print(n // 2 + 1)
       print(1, 2, end = " ")
       for i in range(n // 4):
           print(i * 4 + 4, i * 4 + 7, end = " ")
       print("\n", n // 2, sep = "")
       print(3, end = " ")
       for i in range(n // 4):
           print(i * 4 + 5, i * 4 + 6, end = " ")
       print("")
