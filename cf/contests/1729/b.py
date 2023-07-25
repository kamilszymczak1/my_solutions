for _ in range(int(input())):
    n = int(input())
    s = input()
    i = n - 1
    
    t = "abcdefghijklmnopqrstuvwxyz"
    
    answer = []
    
    while i >= 0:
        my_id = 0
        if s[i] == '0':
            my_id = 10 * int(s[i - 2]) + int(s[i - 1])
            i -= 3
        else:
            my_id = int(s[i])
            i -= 1
        answer.append(t[my_id - 1])
        
    for i in range(len(answer)):
        print(answer[len(answer) - i - 1], end = "")
    print("")
