#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <queue>
#include <map>
#include <set>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<vector<int>>sons(n);
    for(int i = 1; i < n; i++) {
        int x; scanf("%d", &x); x--;
        sons[x].push_back(i);
    }
    vector<long long>l(n), r(n);
    for(int i = 0; i < n; i++)
        scanf("%lld%lld", &l[i], &r[i]);
    
    vector<long long>op(n), hi(n);
    
    for(int i = n - 1; i >= 0; i--) {
        
        if(sons[i].size() == 0) {
            op[i] = 1;
            hi[i] = r[i];
        } else {
            
            long long max_son = 0;
            for(int j : sons[i]) {
                max_son += hi[j];
                op[i] += op[j];
            }
            
            if(max_son < l[i]) {
                op[i]++;
                hi[i] = r[i];
            } else {
                hi[i] = min(max_son, r[i]);
            }
        }
        
    }
    
    printf("%lld\n", op[0]);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
