#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
#include <queue>
#include <stack>
#include <cmath>
#include <cstring>

using namespace std;


const long long inf = 1ll << 60;
const int MAX_N = 5007;

char a[MAX_N], b[MAX_N];

void test_case() {
    int n; scanf("%d", &n);
    long long x, y; scanf("%lld%lld", &x, &y);
    scanf("%s", a);
    scanf("%s", b);
    vector<int>ind;
    
    for(int i = 0; i < n; i++) {
        if(a[i] != b[i]){ 
            ind.push_back(i);
        }
    }
    
    if(ind.size() == 0) {
        printf("0\n");
        return;
    }
    
    if(ind.size() % 2 == 0) {
        if(ind.size() > 2) {
            printf("%lld\n", ind.size() / 2 * y);
        } else {
            if(ind[0] + 1 == ind[1]) {
                printf("%lld\n", min(x, 2 * y));
            } else {
                printf("%lld\n", y);
            }
        }
    } else {
        printf("-1\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}

