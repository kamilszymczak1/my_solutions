#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int ceil(int x, int y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

void test_case() {
    int n; scanf("%d", &n);
    vector<int>a(n), b(n);
    for(int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    for(int j = 0; j < n; j++)
        scanf("%d", &b[j]);
    vector<int>ans;
    for(int k = 1; k <= n; k++) {
        
        bool ok = true;
        
        for(int i = 0; i < n; i++) {
            
            if(a[i] > k * ceil(b[i], k)) {
                ok = false;
            }
        }
        
        if(ok)
            ans.push_back(k);
        
    }
    
    printf("%d\n", (int)ans.size());
    for(int x : ans)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
