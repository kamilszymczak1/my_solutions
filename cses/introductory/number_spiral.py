for _ in range(int(input())):
    row, col = map(int, input().split())
    
    if max(row, col) % 2 == 1:
        row, col = col, row
    
    base = (max(row, col) - 1) ** 2 + row
    
    if row == max(row, col):
        base += row - col
        
    print(base)
