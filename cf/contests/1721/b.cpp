#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <stack>
#include <bitset>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

void test_case() {
    int n, m, x, y, d; scanf("%d%d%d%d%d", &n, &m, &x, &y, &d);
    
    bool answer = (x - d > 1 && y + d < m) || (x + d < n && y - d > 1);
    if(answer) {
        printf("%d\n", n + m - 2);
    } else {
        printf("-1\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
