import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))
    k = [(x - y, i) for i, (x, y) in enumerate(zip(a, b))]
    k.sort()
    answer = []
    for value, index in k:
        if value == k[-1][0]:
            answer.append(index + 1)
    print(len(answer))
    print(*answer)
    
    
