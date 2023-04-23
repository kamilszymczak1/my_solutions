#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdio>
#include <set>
#include <cstring>

using namespace std;

const long long mod = (119 << 23) + 1, B = 29;
const int MAX_N = 300'007;
char c[MAX_N];

int main() {
    int q; scanf("%d", &q);
    
    vector<map<int, int>>occ(MAX_N + 1);
    set<int>lengths;
    vector<int>len_count(MAX_N + 1), b_pow(MAX_N + 1);
    b_pow[0] = 1;
    for(int i = 1; i <= MAX_N; i++)
        b_pow[i] = b_pow[i - 1] * B % mod;
    while(q--) {
        int t; scanf("%d", &t);
        scanf("%s", c);
        int n = strlen(c);
        if(t < 3) {
            int h = 0;
            for(int i = 0; i < n; i++)
                h = (B * h + c[i] - 'a' + 1) % mod;
            occ[n][h] += 3 - 2 * t;
            
            if(t == 1 && len_count[n] == 0)
                lengths.insert(n);
            if(t == 2 && len_count[n] == 1)
                lengths.erase(lengths.find(n));
            len_count[n] += 3 - 2 * t;
        } else {
            long long result = 0;
            for(int x : lengths) {
                if(x > n)
                    break;
                int h = 0;
                for(int i = 0; i < x; i++)
                    h = (h * B + c[i] - 'a' + 1) % mod;
                for(int i = 0; i <= n - x; i++) {
                    auto it = occ[x].find(h);
                    if(it != occ[x].end())
                        result += it -> second;
                    h = (h - (b_pow[x - 1] * (c[i] - 'a' + 1ll)) % mod + mod) % mod;
                    h = (h * B + c[i + x] - 'a' + 1) % mod;
                }
            }
            printf("%lld\n", result);
            fflush(stdout);
        }
    }
}
