#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <cstring>
#include <cmath>

using namespace std;

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<long long>>a(n, vector<long long>(m));
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }
    vector<pair<long long, long long>>v;
    for(int i = 0; i < n; i++) {
        long long to_left = 0, to_right = 0;
        vector<long long>x = a[i], y = a[(i + 1) % n];
        for(int j = 0; j < m - 1; j++) {
            if(x[j] < y[j]) {
                long long diff = y[j] - x[j];
                x[j] += diff;
                x[j + 1] -= diff;
                to_left += diff;
            } else {
                long long diff = x[j] - y[j];
                x[j] -= diff;
                x[j + 1] += diff;
                to_right += diff;
            }
            
        }
        
        if(to_left != to_right)
            v.emplace_back(i, to_left - to_right);
    }
    
    sort(v.begin(), v.end());
    
    if(v[0].first == 0) {
        if(v[1].first == n - 1) {
            printf("1 ");
        } else {
            printf("2 ");
        }
    } else {
        printf("%d ", (v[0].first + 1) % n + 1);
    }
    
    printf("%lld\n", abs(v[0].second));
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
