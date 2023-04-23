#include <cstdio>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

const long long mod = 998244353;

int dist(pair<int, int>&a, pair<int, int>&b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int mod_pow(int x, int exp) {
    if(exp == 0)
        return 1;
    int result = mod_pow(x, exp / 2);
    result = (1ll * result * result) % mod;
    if(exp % 2 == 1)
        result = (1ll * result * x) % mod;
    return result;
}

int main() {
    int n; scanf("%d", &n);
    vector<pair<int, int>>points(n);
    for(int i = 0; i < n; i++)
        scanf("%d%d", &points[i].first, &points[i].second);
    
    vector<int>closest_dist(n, 1 << 30);
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int d = dist(points[i], points[j]);
            closest_dist[i] = min(closest_dist[i], d);
            closest_dist[j] = min(closest_dist[j], d);
        }
    }
    
    vector<set<int>>closest(n);
    for(int i = 0; i < n; i++)
        closest[i].insert(i);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(dist(points[i], points[j]) == closest_dist[i]) {
                closest[i].insert(j);
            }
        }
    }
    
    vector<bool>taken(n);
    vector<int>groups(5);
    
    for(int i = 0; i < n; i++) {
        if(taken[i])
            continue;
        bool ok = true;
        for(int j : closest[i]) {
            if(closest_dist[i] != closest_dist[j])
                ok = false;
            if(closest[i] != closest[j])
                ok = false;
        }
        
        if(ok) {
            for(int j : closest[i])
                taken[j] = true;
            groups[closest[i].size()]++;
        } else {
            taken[i] = true;
            groups[1]++;
        }
    }
    
    vector<vector<int>>choose(n + 1);
    for(int i = 0; i <= n; i++) {
        choose[i].resize(i + 1);
        choose[i][0] = choose[i][i] = 1;
        for(int j = 1; j < i; j++)
            choose[i][j] = (choose[i - 1][j - 1] + choose[i - 1][j]) % mod;
    }
    vector<int>fact(n + 1, 1);
    for(int i = 1; i <= n; i++)
        fact[i] = (1ll * fact[i - 1] * i) % mod;
    
    int result = 0;
    for(int used_2 = 0; used_2 <= groups[2]; used_2++) {
        for(int used_3 = 0; used_3 <= groups[3]; used_3++) {
            for(int used_4 = 0; used_4 <= groups[4]; used_4++) {
                int used_1 = groups[1] + (groups[2] - used_2) * 2 + (groups[3] - used_3) * 3 + (groups[4] - used_4) * 4;
                
                int groups_total = used_1 + used_2 + used_3 + used_4;
                
                int ways = (1ll * choose[groups[2]][used_2] * choose[groups[3]][used_3]) % mod;
                ways = (1ll * ways * choose[groups[4]][used_4]) % mod;
                ways = (1ll * ways * fact[n]) % mod;
                ways = (1ll * ways * mod_pow(fact[n - groups_total], mod - 2)) % mod;
                result = (result + ways) % mod;
            }
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}
