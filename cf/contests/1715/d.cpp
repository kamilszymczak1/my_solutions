#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <cassert>
#include <cmath>

using namespace std;

struct T {
    int i, j, x;
    T(int _i, int _j, int _x) : i(_i), j(_j), x(_x) {}
};

void test_case() {
    int n, q; scanf("%d%d", &n, &q);
    
    vector<T>t;
    vector<vector<pair<int, int>>>s(n);
    for(int k = 0; k < q; k++) {
        int i, j, x; scanf("%d%d%d", &i, &j, &x);
        t.emplace_back(i - 1, j - 1, x);
        if(t.back().i > t.back().j)
            swap(t.back().i, t.back().j);
        
        s[min(i, j) - 1].emplace_back(max(i, j) - 1, x);
    }
    vector<int>a(n);
    for(int bit = 29; bit >= 0; bit--) {
        vector<bool>sure_zero(n, false);
        
        for(int i = 0; i < q; i++) {
            if((t[i].x >> bit) & 1) {
                
            } else {
                sure_zero[t[i].i] = true;
                sure_zero[t[i].j] = true;
            }
        }
        
        for(int i = 0; i < n; i++) {
            
            if((a[i] >> bit) & 1)
                continue;
            bool must_one = false;
            for(auto [j, x] : s[i]) {
                if((x >> bit) & 1) {
                    if(sure_zero[j] || i == j)
                        must_one = true;
                }
            }
            
            if(must_one) {
                a[i] |= 1 << bit;
            } else {
                for(auto [j, x] : s[i]) {
                    if((x >> bit) & 1) {
                        a[j] |= 1 << bit;
                    }
                }
            }
        }
    }
    
    for(int x : a)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t = 1;
    while(t--)
        test_case();
    return 0;
}
