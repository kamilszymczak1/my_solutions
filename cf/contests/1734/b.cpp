#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    printf("1\n");
    for(int i = 1; i < n; i++) {
        printf("1 ");
        for(int j = 0; j < i - 1; j++)
            printf("0 ");
        printf("1\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
