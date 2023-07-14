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

const long long mod = 998244353;

void TopoDFS(int x, vector<vector<int>>&out, vector<bool>&visited, vector<int>&order) {
    visited[x] = true;
    for(int y : out[x]) {
        if(!visited[y]) {
            TopoDFS(y, out, visited, order);
        }
    }
    order.push_back(x);
}

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    vector<vector<int>>out(n);
    vector<long long>a(n);
    for(auto &x : a)
        scanf("%lld", &x);
    for(int i = 0; i < m; i++) {
        int x, y; scanf("%d%d", &x, &y);
        x--; y--;
        out[x].push_back(y);
    }
    
    long long result = 0;
    for(int i = 0; i < n; i++) {
        bool change = false;
        vector<long long>new_a = a;
        for(auto &x : new_a)
            x = max(0ll, x - 1);
        for(int j = 0; j < n; j++) {
            if(a[j] != 0) {
                change = true;
                for(int k : out[j]) {
                    new_a[k]++;
                }
            }
        }
        if(!change) {
            printf("%d\n", i);
            return;
        }
        swap(new_a, a);
    }
    
    for(auto &x : a)
        x %= mod;
    
    vector<bool>visited(n, false);
    vector<int>order;
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            TopoDFS(i, out, visited, order);
        }
    }
    reverse(order.begin(), order.end());
    for(int x : order) {
        for(int y : out[x]) {
            a[y] += a[x];
            a[y] %= mod;
        }
    }
    printf("%lld\n", (a[order.back()] + n) % mod);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
