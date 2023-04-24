#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<int>dp(n, 1), a(n);
    for(int &x : a)
        scanf("%d", &x);
    
    int answer = 1;
    for(int i = 0; i < n; i++) {
        for(int j = max(0, i - 400); j < i; j++) {
            if((a[j] ^ i) < (a[i] ^ j)) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        answer = max(answer, dp[i]);
    }
    printf("%d\n", answer);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
