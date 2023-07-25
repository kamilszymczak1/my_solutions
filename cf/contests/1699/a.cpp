#include <cstdio>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    if(n % 2 == 1) {
        printf("-1\n");
    } else {
        printf("%d 0 0\n", n / 2);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
