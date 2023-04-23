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
    vector<int>a(n);
    int k; scanf("%d", &k);
    for(int &x : a)
        scanf("%d", &x);
    
    int result = 0;
    for(int i = 0; i < k; i++) {
        a[i]--;
        if(a[i] >= k)
            result++;
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
