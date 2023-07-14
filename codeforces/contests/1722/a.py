for _ in range(int(input())):
    n = int(input())
    s = input()
    count = [0] * 256
    my_name = {"T", "i", "m", "u", "r"}
    
    for x in s:
        count[ord(x)] += 1
        
    if len(my_name) != len(s):
        print("NO")
    else:
        answer = True
        for x in my_name:
            if count[ord(x)] != 1:
                answer = False
        
        print("YES" if answer else "NO")
