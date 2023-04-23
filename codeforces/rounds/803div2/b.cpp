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
    int n, k; scanf("%d%d", &n, &k);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    if(k == 1) {
        printf("%d\n", (n - 1) / 2);
    } else {
        int result = 0;
        for(int i = 1; i < n - 1; i++) {
            if(a[i] > a[i - 1] + a[i + 1]) {
                result++;
            }
        }
        printf("%d\n", result);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
