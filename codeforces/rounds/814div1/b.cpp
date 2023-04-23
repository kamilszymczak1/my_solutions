#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>
#include <set>
#include <cassert>
    
using namespace std;
    
bool get(long long x, vector<long long>&fib, vector<bool>&ans) {
    for(int i = (int)fib.size() - 1; i >= 0; i--) {
        if(x >= fib[i]) {
            ans[i] = true;
            x -= fib[i];
        }
    }
    return x == 0;
}
    
void test_case() {
    int n; scanf("%d", &n);
    if(n == 1) {
        int x; scanf("%d", &x);
        printf("%s\n", x == 1 ? "YES" : "NO");
        return;
    }
    long long v_sum = 0;
    vector<long long>v(n);
    for(auto &x : v) {
        scanf("%lld", &x);
        v_sum += x;
    }
    
    int my_len = -1;
    long long fib_sum = 2;
    vector<long long>fib = {1, 1};
    while(fib.back() < 1e9) {
        if(fib_sum == v_sum)
            my_len = fib.size();
        long long x = fib[fib.size() - 1], y = fib[fib.size() - 2];
        fib.push_back(x + y);
        fib_sum += x + y;
    }
    if(fib_sum == v_sum)
        my_len = fib.size();
    
    if(my_len == -1) {
        printf("NO\n");
        return;
    }
    
    vector<long long>states(1, 0);
    
    for(int i = 0; i < n; i++) {
        vector<bool>b(fib.size());
        if(!get(v[i], fib, b)) {
            printf("NO\n");
            return;
        }
        vector<long long>new_states;
        long long x = 0;
        for(int j = 0; j < (int)fib.size(); j++) {
            if(b[j]) {
                x |= 1ll << j;
            }
        }
        
        if(x < (1ll << my_len)) {
            for(long long t : states) {
                if((t & x) == 0) {
                    new_states.push_back(t ^ x);
                }
            }
        }
        
        int k = 0;
        while(b[k] == false)
            k++;
        
        if(k % 2 == 1) {
            b[k] = false;
            for(k-- ; k >= 0; k -= 2)
                b[k] = true;
            
            x = 0;
            for(int j = 0; j < (int)fib.size(); j++) {
                if(b[j]) {
                    x |= 1ll << j;
                }
            }
            
            if(x < (1ll << my_len)) {
                for(long long t : states) {
                    if((t & x) == 0) {
                        new_states.push_back(t ^ x);
                    }
                }
            } 
        }
        
        swap(states, new_states);
    }
    
    printf("%s\n", states.empty() ? "NO" : "YES");
}
    
int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
