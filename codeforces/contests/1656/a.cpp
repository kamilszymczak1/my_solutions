#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>x(n);
    int lo = 0, hi = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &x[i]);
        if(x[i] > x[hi])
            hi = i;
        if(x[i] < x[lo])
            lo = i;
    }
    printf("%d %d\n", lo + 1, hi + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
