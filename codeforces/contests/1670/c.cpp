#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>
#include <bitset>
#include <map>
#include <queue>

using namespace std;

struct DSU {
    vector<int>f;
    int n, components;
    DSU(int _n) {
        f.resize(_n);
        n = _n;
        components = n;
        for(int i = 0; i < n; i++)
            f[i] = i;
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int a, int b) {
        a = Find(a); b = Find(b);
        if(a != b) {
            components--;
            f[a] = b;
        }
    }
    int Components() {
        return components;
    }
};

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n), aRev(n), b(n), bRev(n), d(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]); a[i]--;
        aRev[a[i]] = i;
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &b[i]); b[i]--;
        bRev[b[i]] = i;
    }
    DSU dsu(n);
    for(int i = 0; i < n; i++) {
        dsu.Union(i, bRev[a[i]]);
        dsu.Union(i, aRev[b[i]]);
    }
    int ans = dsu.Components();
    vector<int>marked(n, false);
    for(int i = 0; i < n; i++) {
        int d; scanf("%d", &d); d--;
        if(a[i] == b[i]) {
            ans--;
            continue;
        }
        if(d != -1) {
            int x = dsu.Find(i);
            if(marked[x] == false) {
                ans--;
                marked[x] = true;
            }
        }
    }
    int result = 1;
    const int mod = 1'000'000'007;
    for(int i = 0; i < ans; i++) {
        result = result + result;
        if(result >= mod)
            result -= mod;
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
}
