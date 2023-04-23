for _ in range(int(input())):
    a, b, c = map(int, input().split())
    
    if a < abs(b - c) + c:
        print(1)
    elif a > abs(b - c) + c:
        print(2)
    else:
        print(3)
