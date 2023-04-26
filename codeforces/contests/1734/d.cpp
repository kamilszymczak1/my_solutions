#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n, k; scanf("%d%d", &n, &k);
    k--;
    vector<long long>a(n);
    for(int i = 0; i < n; i++)
        scanf("%lld", &a[i]);
    
    int l = k, r = k;
    int ll = k, rr = k;
    long long l_sum = 0, r_sum = 0;
    long long l_min = 0, r_min = 0;
    
    long long my_hp = a[k];
    
    while(l > 0 && r < n) {
        while(ll > 0 && l_sum <= 0) {
            ll--;
            l_sum += a[ll];
            l_min = min(l_min, l_sum);
        }
        
        while(rr < n - 1 && r_sum <= 0) {
            rr++;
            r_sum += a[rr];
            r_min = min(r_min, r_sum);
        }
        
        bool move = false;
        
        if(l_sum >= 0 && my_hp + l_min >= 0 && ll != l) {
            my_hp += l_sum;
            l = ll;
            l_sum = 0;
            l_min = 0;
            move = true;
        }
        
        if(r_sum >= 0 && my_hp + r_min >= 0 && rr != r) {
            my_hp += r_sum;
            r = rr;
            r_sum = 0;
            r_min = 0;
            move = true;
        }
        
        if(!move)
            break;
    }
    
    if(l <= 0 || r >= n - 1) {
        printf("YES\n");
        return;
    }
    
    while(ll > 0) {
        ll--;
        l_sum += a[ll];
        l_min = min(l_sum, l_min);
    }
    
    while(rr < n - 1) {
        rr++;
        r_sum += a[rr];
        r_min = min(r_sum, r_min);
    }
    
    if(r_min + my_hp < 0 && l_min + my_hp < 0) {
        printf("NO\n");
    } else {
        printf("YES\n");
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
}
