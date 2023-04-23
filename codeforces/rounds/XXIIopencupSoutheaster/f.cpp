#include <cstdio>
#include <set>

using namespace std;

char c[2'000'007], t[2'000'007];
const long long inf = 1ll << 60;

int main() {
    long long n, x, r, p, k; scanf("%lld%lld%lld%lld%lld", &n, &x, &r, &p, &k);
    scanf("%s", c);
    
    for(int i = 0; i < n; i++)
        t[i] = '0';
    
    long long answer = -inf;
    
    long long local = 0;
    int blocked_count = 0;
    for(int i = 0; i < n; i++) {
        
        if(c[i] == '1') {
            if(blocked_count < k) {
                local += (n - i) * p;
                blocked_count++;
                t[i] = '1';
            } else {
                local -= (n - i) * r;
            }
        }
    }
    
    set<int>free_indices;
    for(int i = 0; i < n; i++) {
        if(t[i] == '0') {
            free_indices.insert(i);
        }
    }
    
    while(n - free_indices.size() < k) {
        int i = *free_indices.begin();
        free_indices.erase(free_indices.begin());
        t[i] = '1';
        local += (n - i) * p;
    }
    
    answer = max(answer, local);
    
    for(int i = n - 1; i >= 0; i--) {
        
        if(c[i] == '1' && free_indices.find(i) == free_indices.end()) {
            local -= (n - i) * (p + r);
            free_indices.insert(i);
            t[i] = '0';
        }
        
        while(n - free_indices.size() < k) {
            int j = *free_indices.begin();
            free_indices.erase(free_indices.begin());
            t[j] = '1';
            local += (n - j) * p;
        }
        
        answer = max(answer, local);
    }
    printf("%lld\n", answer + x * n);
}
