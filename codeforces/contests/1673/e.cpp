#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

void TestCase() {
    int n, k; scanf("%d%d", &n, &k);
    vector<int>b(n);
    for(int &x : b)
        scanf("%d", &x);
    
    vector<vector<bool>>ways(3, vector<bool>(20, 0));
    
    int initValue = max(n - 20, 0);
    
    for(int fixed = 0; fixed <= 2; fixed++) {
        for(int i = 0; i < 20; i++) {
            int places = initValue + i, a = initValue + i - fixed;
            int balance = 0;
            for(int j = 0; j <= a; j++) {
                if(j + fixed >= k)
                    ways[fixed][i] = ways[fixed][i] ^ (balance == 0);
                balance += __builtin_ctz(j + 1) - __builtin_ctz(a - j);
            }
        }
    }
    
    
    vector<bool>ans(1 << 20, 0);
    
    for(int len = 1; len <= 20; len++) {
        for(int i = 0; i + len <= n; i++) {
            long long exponentA = b[i], exponentB = 0;
            for(int j = 1; j < len; j++) {
                exponentB += b[i + j];
                if(exponentB >= 20 || exponentA * (1ll << exponentB) >= (1 << 20))
                    exponentA = 0;
            }
            
            int places = n - len, fixed = (i == 0 ? 0 : 1) + (i + len == n ? 0 : 1);
            if(places < k || exponentA == 0)
                continue;
            
            int exponent = exponentA * (1ll << exponentB);
            
            ans[exponent] = ans[exponent] ^ ways[fixed][places - initValue];
        }
    }
    
    int j = (1 << 20) - 1;
    while(j >= 0 && ans[j] == false)
        j--;
    for(int i = max(j, 0); i >= 0; i--)
        printf("%d", (int)ans[i]);
    printf("\n");
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
