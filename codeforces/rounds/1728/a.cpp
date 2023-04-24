#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    
    int hi = 0;
    for(int i = 1; i < n; i++) {
        if(a[i] > a[hi]) {
            hi = i;
        }
    }
    printf("%d\n", hi + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
