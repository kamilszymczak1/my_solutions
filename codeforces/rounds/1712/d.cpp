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
    int n, k; scanf("%d%d", &n, &k);
    
    map<int, vector<int>>m;
    vector<int>a(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        m[a[i]].push_back(i);
    }
    
    if(n == k) {
        printf("1000000000\n");
        return;
    }
    
    vector<int>b = a;
    sort(b.begin(), b.end());
    for(int i = 0; i < 10; i++)
        b.push_back(1'000'000'000);
    
    int result = 0;
    for(int i = 0; i < n - 1; i++) {
        
        if(k >= 2) {
            int x = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            int y = upper_bound(b.begin(), b.end(), a[i + 1]) - b.begin() - 1;
            
            if(x > y)
                swap(x, y);
            int t = 0;
            if(x <= k - 2) {
                if(y <= k - 1)
                    t = b[k];
                else
                    t = b[k - 1];
            } else {
                t = b[k - 2];
            }
            
            result = max(result, 2 * t);
        }
        
        if(k >= 1) {
            int x = lower_bound(b.begin(), b.end(), min(a[i], a[i + 1])) - b.begin();
            
            int t = 0;
            if(x <= k - 1)
                t = b[k];
            else
                t = b[k - 1];
            
            result = max(result, min(max(a[i], a[i + 1]), 2 * t));
        }
        
        result = max(result, min(min(a[i], a[i + 1]), b[k] * 2));
    }
    result = min(result, 1'000'000'000);
    
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}

