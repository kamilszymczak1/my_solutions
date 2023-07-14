#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 300'007;
int x[MAX_N], fib[MAX_N], a[MAX_N], n, q, mod, nonZeroCount = 0;

void Add(int &value, int toAdd) {
    value += toAdd;
    if(value >= mod)
        value -= mod;
}

void Subtract(int &value, int toSubtract) {
    value -= toSubtract;
    if(value < 0)
        value += mod;
}

void Update(int i, int value) {
    if(x[i] == 0)
        nonZeroCount++;
    Add(x[i], value);
    if(x[i] == 0)
        nonZeroCount--;
}

void TestCase() {
    scanf("%d%d%d", &n, &q, &mod);
    fib[0] = 0; fib[1] = 1;
    for(int i = 2; i < n + 2; i++) {
        Add(fib[i], fib[i - 1]);
        Add(fib[i], fib[i - 2]);
    }
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i + 2]);
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        Subtract(a[i + 2], x);
    }
    for(int i = 2; i < n + 2; i++) {
        x[i] = a[i];
        Subtract(x[i], a[i - 1]);
        Subtract(x[i], a[i - 2]);
        nonZeroCount += x[i] != 0;
    }
    
    while(q--) {
        char c; do c = getchar(); while(c != 'A' && c != 'B');
        int l, r; scanf("%d%d", &l, &r);
        if(c == 'A') {
            Update(l + 1, 1);
            if(r + 2 < n + 2 && fib[r - l + 2] != 0)
                Update(r + 2, mod - fib[r - l + 2]);
            if(r + 3 < n + 2 && fib[r - l + 1] != 0)
                Update(r + 3, mod - fib[r - l + 1]);
        } else {
            Update(l + 1, mod - 1);
            if(r + 2 < n + 2)
                Update(r + 2, fib[r - l + 2]);
            if(r + 3 < n + 2)
                Update(r + 3, fib[r - l + 1]);
        }
        if(nonZeroCount) {
            printf("NO\n");
        } else {
            printf("YES\n");
        }
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    
    return 0;
}
