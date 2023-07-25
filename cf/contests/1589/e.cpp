#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 60;

void test_case() {
    int n; scanf("%d", &n);
    
    vector<long long>p(n + 1);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
        p[i] -= p[i - 1];
    }
    
    vector<vector<pair<long long, int>>>s(2);
    s[0].emplace_back(-inf, n + 1);
    s[1].emplace_back(-inf, n + 1);
    
    vector<map<long long, vector<int>>>m(2);
    for(int i = 1; i <= n; i++)
        m[i & 1][p[i]].push_back(i);
    
    long long result = 0;
    
    for(int i = n; i >= 1; i--) {
        
        int b = i & 1;
        
        while(s[b].back().first >= p[i])
            s[b].pop_back();
        s[b].emplace_back(p[i], i);
        
        int j = n + 1;
        {
            auto it = lower_bound(s[b].begin(), s[b].end(), make_pair(-p[i - 1], -1));
            it--;
            j = min(j, it -> second);
        }
        
        {
            auto it = lower_bound(s[b ^ 1].begin(), s[b ^ 1].end(), make_pair(p[i - 1], -1));
            it--;
            j = min(j, it -> second);
        }
        
        {
            auto it = m[b].find(-p[i - 1]);
            if(it != m[b].end()) {
                result += lower_bound(it -> second.begin(), it -> second.end(), j + 1) - lower_bound(it -> second.begin(), it -> second.end(), i);
            }
        }
        
        {
            auto it = m[b ^ 1].find(p[i - 1]);
            if(it != m[b ^ 1].end()) {
                result += lower_bound(it -> second.begin(), it -> second.end(), j + 1) - lower_bound(it -> second.begin(), it -> second.end(), i);
            }
        }
    }
    
    printf("%lld\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
