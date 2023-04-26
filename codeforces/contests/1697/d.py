A = 26
 
 
def query1(x):
    print("?", 1, x + 1, flush=True)
    return ord(input()) - ord('a')
 
def query2(l, r):
    print("?", 2, l + 1, r + 1, flush=True)
    return int(input())
 
n = int(input())
 
last_appearance = [-1] * A
discovered_letters = 0
 
answer = [0] * n
 
for i in range(n):
    
    if query2(0, i) > discovered_letters:
        discovered_letters += 1
        answer[i] = query1(i)
        last_appearance[answer[i]] = i
    else:
        my_list = []
        for j in range(A):
            if last_appearance[j] != -1:
                my_list.append((last_appearance[j], j))
        my_list.sort()
        
        l, r = 0, len(my_list) - 1
        while l <= r:
            mid = (l + r) // 2
            
            if query2(my_list[mid][0], i) == len(my_list) - mid + 1:
                r = mid - 1
            else:
                l = mid + 1
        
        answer[i] = my_list[l - 1][1]
        last_appearance[answer[i]] = i
 
print("!", end = " ", flush = True)
[print(chr(x + ord('a')), end = "", flush=True) for x in answer]
print("", flush=True)
