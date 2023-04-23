#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    if(n == 1) {
        printf("0\n");
        return;
    }
    
    vector<pair<int, int>>op;
    op.emplace_back(0, n - 1);
    if((a[0] + a[n - 1]) % 2 == 0) {
        a[0] = a[n - 1];
    } else {
        a[n - 1] = a[0];
    }
    
    for(int i = 1; i < n - 1; i++) {
        if((a[0] + a[i]) % 2 == 0) {
            a[i] = a[0];
            op.emplace_back(i, n - 1);
        } else {
            a[i] = a[0];
            op.emplace_back(0, i);
        }
    }
    
    printf("%d\n", (int)op.size());
    for(auto [x, y] : op)
        printf("%d %d\n", x + 1, y + 1);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
