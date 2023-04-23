#include <cstdio>
#include <vector>

using namespace std;

void test_case() {
    int n; scanf("%d", &n);
    vector<long long>a(n + 2), p(n + 2), my_sum(n + 2);
    for(int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
        p[i] = a[i] + p[i - 1];
    }
    a[0] = a[n + 1] = 1ll << 60;
    
    vector<pair<int, long long>>s; //index, minimum on my interval
    
    s.emplace_back(0, 0);
    
    for(int i = 1; i <= n; i++) {
        long long my_min = 1ll << 60;
        while(!s.empty() && a[s.back().first] <= a[i]) {
            my_min = min(my_min, s.back().second);
            s.pop_back();
        }
        my_min = min(my_min, p[s.back().first]);
        s.emplace_back(i, min(my_min, p[i]));
        my_sum[i] += p[i] - my_min;
    }
    
    while(!s.empty())
        s.pop_back();
    
    s.emplace_back(n + 1, p[n]);
    for(int i = n; i >= 1; i--) {
        long long my_max = p[i];
        while(!s.empty() && a[s.back().first] <= a[i]) {
            my_max = max(my_max, s.back().second);
            s.pop_back();
        }
        s.emplace_back(i, my_max);
        my_sum[i] += my_max - p[i];
    }
    
    for(int i = 1; i <= n; i++) {
        if(my_sum[i] > a[i]) {
            printf("NO\n");
            return;
        }
    }
    
    printf("YES\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
