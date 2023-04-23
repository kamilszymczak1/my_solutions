for _ in range(int(input())):
    s = input()
    n = len(s)
    
    A = 26
    
    where = [[] for i in range(A)]
    
    for i in range(n):
        where[ord(s[i]) - ord("a")].append(i)
    
    dist = abs(ord(s[0]) - ord(s[n - 1]))
    
    tiles = []
    
    i = ord(s[0]) - ord('a')
    if s[0] > s[n - 1]:
        while i >= ord(s[n - 1]) - ord('a'):
            for x in where[i]:
                tiles.append(x)
            i -= 1
    else:
        while i <= ord(s[n - 1]) - ord('a'):
            for x in where[i]:
                tiles.append(x)
            i += 1
            
    print(dist, len(tiles))
    for x in tiles:
        print(x + 1, end = " ")
    print("")
