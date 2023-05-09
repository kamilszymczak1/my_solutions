def number_of_ways(n):
    if n <= 3:
        a = [0, 0, 2 * 3, 4 * 7]
        return a[n]

    A = max(0, (n - 4) ** 2)
    B = max(0, (n - 4) * 4)
    
    tiles = n * n
    total_ways = tiles * (tiles - 1) // 2
    
    sub = A * 8 + B * 10 + 48
    
    total_ways -= sub // 2
    
    return total_ways

n = int(input())
for i in range(1, n + 1):
    print(number_of_ways(i))
