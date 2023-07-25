#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cmath>
#include <cstring>

using namespace std;

void Gen(int n, vector<int>&p) {
    if(n == 2) {
        p[0] = 1;
        p[1] = 0;
        return;
    } else if(n == 1) {
        p[0] = 0;
        return;
    } else if(n <= 0)
        return;
    int hi = 2 * n - 2;
    int t = sqrt(hi);
    t = t * t;
    
    int diff = t - (n - 1);
    
    for(int i = 1; i <= n - diff; i++)
        p[n - i] = diff + i - 1;
    
    Gen(n - (n - diff), p);
}

void test_case() {
    int n; scanf("%d", &n);
    vector<int>p(n);
    Gen(n, p);
    for(int x : p)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
