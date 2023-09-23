def count_lines(w, l):
    i = 0
    lines = 0
    while i < len(l):
        j = i
        current_len = l[i]
        while j < len(l) - 1 and current_len + l[j + 1] + 1 <= w:
            current_len += l[j + 1] + 1
            j += 1
        i = j + 1
        lines += 1
    return lines


n, m = map(int, input().split())

l = list(map(int, input().split()))

lo, hi = max(l), sum(l) + n - 1

while lo < hi:
    
    mid = (lo + hi) // 2
    
    if count_lines(mid, l) <= m:
        hi = mid
    else:
        lo = mid + 1
        
print(lo)
