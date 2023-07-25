#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <queue>

using namespace std;

const int inf = 1'000'000'000;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    
    int result = -inf;
    for(int i = 0; i < n; i++) {
        int t = a[(i + n - 1) % n] - a[i];
        result = max(result, t);
    }
    
    for(int i = 1; i < n; i++)
        result = max(result, a[i] - a[0]);
    
    for(int i = 0; i < n - 1; i++)
        result = max(result, a[n - 1] - a[i]);
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
