n = int(input())
answer, last = 0, 0
for x in map(int, input().split()):
    answer += max(0, last - x)
    last = max(last, x)
print(answer)
    
