#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

void CountBits(vector<int>&v, int x) {
    for(int i = 0; x; i++) {
        v[i] += x & 1;
        x /= 2;
    }
}

void TestCase() {
    int l, r; scanf("%d%d", &l, &r);
    vector<int>a(17, 0), b(17, 0);
    for(int i = l; i <= r; i++) {
        int x; scanf("%d", &x);
        CountBits(a, x);
        CountBits(b, i);
    }
    
    int x = 0;
    for(int i = 0; i < 17; i++) {
        if(a[i] != b[i])
            x |= 1 << i;
    }
    printf("%d\n", x);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
