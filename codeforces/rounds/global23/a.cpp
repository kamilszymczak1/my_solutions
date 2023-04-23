#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n, k; scanf("%d%d", &n, &k);
    int zero = 0, one = 0;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        if(x == 0)
            zero++;
        else
            one++;
    }
    
    if(zero == n) {
        printf("NO\n");
    } else {
        if(k <= n) {
            printf("YES\n");
        } else {
            if(one == n) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }
        }
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
