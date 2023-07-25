#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>
#include <set>

using namespace std;

void test_case() {
    int n, q; scanf("%d%d", &n, &q);
    vector<int>p(1, 1);
    for(int i = 2, m = n; i <= m; i++) {
        if(m % i == 0) {
            p.push_back(n / i);
            while(m % i == 0)
                m /= i;
        }
    }
    
    vector<vector<long long>>t(p.size());
    for(int i = 0; i < (int)p.size(); i++)
        t[i].resize(p[i]);
    
    vector<long long>a(n);
    for(int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        for(int j = 0; j < (int)p.size(); j++) {
            t[j][i % p[j]] += a[i] * p[j];
        }
    }
    
    multiset<long long>s;
    for(int i = 0; i < (int)p.size(); i++) {
        for(int j = 0; j < p[i]; j++) {
            s.insert(-t[i][j]);
        }
    }
    
    printf("%lld\n", -(*s.begin()));
    
    while(q--) {
        int pos; scanf("%d", &pos); pos--;
        long long x; scanf("%lld", &x);
        for(int i = 0; i < (int)p.size(); i++) {
            s.erase(s.find(-t[i][pos % p[i]]));
            t[i][pos % p[i]] -= a[pos] * p[i];
        }
        a[pos] = x;
        for(int i = 0; i < (int)p.size(); i++) {
            t[i][pos % p[i]] += a[pos] * p[i];
            s.insert(-t[i][pos % p[i]]);
        }
        
        printf("%lld\n", -(*s.begin()));
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
