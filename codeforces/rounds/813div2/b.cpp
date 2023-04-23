#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <bitset>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>p(n + 1);
    for(int i = 1; i <= n; i++)
        p[i] = i;
    
    if(n % 2 == 0) {
        for(int i = 1; i <= n; i += 2) {
            swap(p[i], p[i + 1]);
        }
    } else {
        for(int i = 2; i <= n; i += 2) {
            swap(p[i], p[i + 1]);
        }
    }
    
    for(int i = 1; i <= n; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
