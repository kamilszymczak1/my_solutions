#include <cstdio>
#include <algorithm>
#include <vector>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    int z; scanf("%d", &z);
    int result = 0;
    for(int i = 0; i < n; i++) {
        int x; scanf("%d", &x);
        result = max(result, x | z);
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
