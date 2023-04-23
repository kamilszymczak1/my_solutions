
def f(x):
    while x % 10 != 0 and x % 10 != 2:
        x += x % 10
    return x

def test_case():
    n = int(input())
    a = list(map(int, input().split()))
    a = list(map(f, a))
    
    zero, two = -1, -1
    for x in a:
        if x % 10 == 0:
            if zero == -1:
                zero = x
            elif zero != x:
                print("NO")
                return
        else:
            if two == -1:
                two = x
            elif abs(x - two) % 20 != 0:
                print("NO")
                return
            
    if zero == -1 or two == -1:
        print("YES")
    else:
        print("NO")


for i in range(int(input())):
    test_case()
