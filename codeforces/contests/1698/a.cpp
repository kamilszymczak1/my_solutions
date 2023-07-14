#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    int all_xor = 0;
    vector<int>a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        all_xor ^= a[i];
    }
    
    for(int i = 0; i < n; i++) {
        all_xor ^= a[i];
        if(a[i] == all_xor) {
            printf("%d\n", a[i]);
            return;
        }
        all_xor ^= a[i];
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
