for _ in range(int(input())):
    n = int(input())
    solved = [False] * 26
    result = 0
    for c in input():
        x = ord(c) - ord('A')
        if solved[x]:
            result += 1
        else:
            result += 2
            solved[x] = True
    
    print(result)
