#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const int MAX_N = 200007;

char c[MAX_N];

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    scanf("%s", c);
    for(int i = 0; i < n; i++)
        c[i] -= '0';
    int currentK = k;
    vector<int>f(n);
    vector<char>ans(n);
    for(int i = 0; i < n; i++) {
        if(currentK == 0) {
            f[i] = 0;
            ans[i] = c[i] ^ (k % 2);
        } else {
            if(c[i] == k % 2) {
                currentK -= 1;
                ans[i] = c[i] ^ (k % 2) ^ 1;
                f[i] = 1;
            } else {
                ans[i] = c[i] ^ (k % 2);
                f[i] = 0;
            }
        }
    }
    
    if(currentK > 0) {
        ans[n - 1] = ans[n - 1] ^ (currentK % 2);
        f[n - 1] += currentK;
    }
    
    for(int i = 0; i < n; i++) {
        printf("%c", ans[i] + '0');
    }
    printf("\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", f[i]);
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
