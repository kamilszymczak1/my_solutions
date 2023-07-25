#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

const long long mod = 998244353;

void transform(vector<int>&v) {
    int n = v.size();
    vector<int>new_v(v.size(), -1);
    for(int i = 0; i < n; i++) {
        if(v[i] != -1)
            new_v[v[i]] = i;
    }
    swap(v, new_v);
}

void test_case() {
    int n, s; scanf("%d%d", &n, &s);
    vector<int>a(n), b(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &b[i]);
        b[i] = max(b[i] - 1, -1);
    }
    transform(a);
    transform(b);
    vector<int>where_in_b(n, -1);
    for(int i = 0; i < n; i++) {
        if(b[i] != -1) {
            where_in_b[b[i]] = i;
        }
    }
    long long result = 1;
    int free_spots = 0;
    for(int i = 1; i <= s; i++)
        free_spots += b[n - i] == -1;
    for(int i = 1; i <= n; i++) {
        if(n - i - s >= 0)
            free_spots += b[n - i - s] == -1;
        int current = a[n - i];
        if(where_in_b[current] == -1) {
            result = result * free_spots % mod;
            free_spots--;
        } else {
            if(where_in_b[current] < n - i - s) {
                printf("0\n");
                return;
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
