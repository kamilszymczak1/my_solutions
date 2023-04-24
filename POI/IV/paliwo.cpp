#include <algorithm>
#include <cstdio>
#include <ctype.h>

using namespace std;
constexpr int MAX_N = 1000007;
constexpr int leafCount = 1 << 10;
long long c[MAX_N], d[MAX_N], pos[MAX_N], n, p;
int tree[leafCount << 1], nextCheaper[MAX_N];

int NextInt() {
    int c, result = 0;
    do {
        c = getchar_unlocked();
    } while(!isdigit(c));
    do {
        result = result * 10 + c - '0';
        c = getchar_unlocked();
    } while(isdigit(c));
    return result;
}

int PrefixMin(int i) {
    int result = tree[i += leafCount];
    for(; i; i >>= 1) {
        if(i & 1) {
            result = min(result, tree[i - 1]);
        }
    }
    return result;
}

void Insert(int i, int value) {
    tree[i += leafCount] = value;
    for(i >>= 1; i; i >>= 1) {
        tree[i] = min(tree[i << 1], tree[(i << 1) + 1]);
    }
}


int main() {
    p = NextInt();
    n = NextInt();
    for(int i = 0; i < n; i++) {
        c[i] = NextInt();
        d[i] = NextInt();
    }
    for(int i = 1; i <= n; i++) {
        pos[i] = pos[i - 1] + d[i - 1];
    }
    
    fill(tree, tree + leafCount * 2, n);
    for(int i = n - 1; i >= 0; i--) {
        nextCheaper[i] = PrefixMin(c[i]);
        Insert(c[i], i);
    }
    
    long long fuel = 0, result = 0;
    for(int i = 0; i < n && fuel < pos[n] - pos[i]; i++) {
        if(fuel < pos[nextCheaper[i]] - pos[i]) {
            const long long fuelToBuy = min(pos[nextCheaper[i]] - pos[i] - fuel, p - fuel);
            result += fuelToBuy * c[i];
            fuel += fuelToBuy;
        }
        fuel -= d[i];
    }
    
    printf("%lld\n", result);
    
    return 0;
}
