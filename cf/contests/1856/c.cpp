#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
void test_case() {
    int n; cin >> n;
    long long k; cin >> k;
    vector<long long>a(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    
    long long lo = 0, hi = 1ll << 60;
    
    while(lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        
        
        bool ans = false;
        for(int i = 1; i <= n; i++) {
            long long my_k = k;
            for(int j = 0; i + j <= n; j++) {
                long long target = mid - j;
                if(target <= a[i + j]) {
                    ans = true;
                }
                my_k -= target - a[i + j];
                if(my_k < 0)
                    break;
            }
            
        }
        
        if(ans == true) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    
    cout << lo << '\n';
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
