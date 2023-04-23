#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>
#include <map>
#include <stack>
#include <set>

using namespace std;

const long long inf = 1 << 60;

void test_case() {
    int n; scanf("%d", &n);
    long long balance = 0;
    vector<long long>changes(n);
    for(int i = 0; i < n; i++) {
        long long a, b; scanf("%lld%lld", &a, &b);
        balance += b;
        changes.push_back(a - b);
    }
    sort(changes.begin(), changes.end(), greater<int>());
    
    vector<long long>best_cost(n + 1);
    best_cost[0] = balance;
    for(int i = 1; i <= n; i++)
        best_cost[i] = best_cost[i - 1] + changes[i];
    
    int m; scanf("%d", &m);
    vector<vector<pair<int, int>>>queries(n + 1);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        queries[x].emplace_back(y, i);
    }
    
    
    
    vector<int>smallest_prime(n + 1, n + 2);
    for(int i = 2; i <= n; i++) {
        if(smallest_prime[i] == n + 2) {
            for(int j = i; j <= n; j += i) {
                smallest_prime[j] = min(smallest_prime[j], i);
            }
        }
    }
    
    vector<long long>v(n + 1, -1);
    stack<int>changed;
    
    vector<long long>answer(m);
    
    for(int x = 1; x <= n; x++) {
        for(int x_count = 0; x_count * x <= n; x_count++) {
            
            int rem = n - x_count * x;
            
            set<int, greater<int>>s;
            s.insert(rem);
            
            v[rem] = max(v[rem], best_cost[x_count * x]);
            
            changed.push(rem);
            
            while(!s.empty()) {
                int x = *s.begin();
                s.erase(s.begin());
                int p = smallest_prime[x];
                int xp = x / p;
                if(v[xp] < v[x]) {
                    v[xp] = v[x];
                    changes.push(xp);
                    if(s.find(xp) == s.end())
                        s.insert(xp);
                }
            }
        }
        
        for(auto [y, ind] : queries[x]) {
            answer[ind] = v[y];
        }
        
        while(!changes.empty()) {
            v[changes.top()] = -1;
            changes.pop();
        }
    }
    
    for(long long x : answers) {
        printf("%lld\n", x);
    }
}

int main() {
    int t = 1;
    while(t--)
        test_case();
    return 0;
}
