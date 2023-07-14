#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <string>

using namespace std;

const long long mod = 998244353;

const int MAX_N = 1 << 18;
char c[MAX_N];

void TestCase() {
    int n; scanf("%d", &n);
    int leafCount = 1 << (n - 1);
    scanf("%s", c);
    vector<string>pre(1 << n, "");
    for(int i = leafCount; i < leafCount * 2; i++)
        pre[i] = c[i - 1];
    
    for(int i = leafCount - 1; i > 0; i--) {
        if(pre[i * 2] > pre[i * 2 + 1]) {
            pre[i] = c[i - 1] + pre[i * 2 + 1] + pre[i * 2];
        } else {
            pre[i] = c[i - 1] + pre[i * 2] + pre[i * 2 + 1];
        }
    }
    
    vector<long long>ans(1 << n, 0);
    for(int i = leafCount; i < leafCount * 2; i++)
        ans[i] = 1;
    
    for(int i = leafCount - 1; i > 0; i--) {
        ans[i] = (ans[i * 2 + 1] * ans[i * 2] * 2) % mod;
        if(pre[i * 2 + 1] == pre[i * 2]) {
            ans[i] = ans[i * 2 + 1] * ans[i * 2] % mod;
        }
    }
    printf("%lld\n", ans[1]);
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
