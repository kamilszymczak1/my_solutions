for _ in range(int(input())):
    t = input()
    S = [input() for i in range(int(input()))]
    
    dp = [1 << 30] * (len(t) + 1)
    parent = [(-1, -1)] * (len(t) + 1)
    
    dp[0] = 0
    
    for i in range(len(t)):
        
        for (s, ind) in zip(S, range(len(S))):
            l = len(s)
            if i - l + 1 >= 0:
                
                
                if s == t[i - l + 1 : i + 1]:
                    
                    for j in range(l):
                        
                        if dp[i - l + 1 + j] + 1 < dp[i + 1]:
                            dp[i + 1] = dp[i - l + 1 + j] + 1
                            parent[i + 1] = (i - l + 1 + j, ind)
                    
    if dp[len(t)] == (1 << 30):
        print("-1")
    else:
        print(dp[len(t)])
        i = len(t)
        while i != 0:
            ind = parent[i][1]
            l = len(S[ind])
            print(ind + 1, i - len(S[ind]) + 1)
            i = parent[i][0]
