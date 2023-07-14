#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cassert>
#include <cmath>

using namespace std;

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    
    if(n == 1 && m == 1) {
        printf("0\n");
        return;
    }
    
    printf("%d\n", n + m - 2 + min(n, m));
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
