#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bitset>
#include <set>
#include <queue>
#include <map>
#include <stack>
#include <cmath>

using namespace std;

void test_case() {
    int n, x; scanf("%d%d", &n, &x);
    vector<long long>cnt(x + 1, 0);
    for(int i = 0; i < n; i++) {
        int a; scanf("%d", &a);
        cnt[a]++;
    }
    
    for(int i = 1; i < x; i++) {
        if(cnt[i] % (i + 1) != 0) {
            printf("No\n");
            return;
        } else {
            cnt[i + 1] += cnt[i] / (i + 1);
        }
    }
    printf("Yes\n");
}

int main() {
    int t = 1;
    while(t--)
        test_case();
    return 0;
}
