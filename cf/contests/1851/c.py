import sys
input = sys.stdin.readline

for _ in range(int(input())):
    n, k = map(int, input().split())
    a = list(map(int, input().split()))
    cnt_left = 1
    index_left = 0
    while index_left < n - 1 and cnt_left < k:
        index_left += 1
        if a[index_left] == a[0]:
            cnt_left += 1
    cnt_right = 1
    index_right = n - 1
    while index_right > 0 and cnt_right < k:
        index_right -= 1
        if a[index_right] == a[n - 1]:
            cnt_right += 1
    
    if cnt_left == k and cnt_right == k and (index_left < index_right or a[0] == a[n - 1]):
        print("Yes")
    else:
        print("No")
