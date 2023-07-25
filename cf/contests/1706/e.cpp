#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cstring>
#include <bitset>

using namespace std;


struct SegTree {
    vector<int>v;
    int leafCount;
    SegTree(vector<int>&k) {
        int n = k.size();
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        v.resize(leafCount * 2);
        for(int i = 0; i < n; i++)
            v[i + leafCount] = k[i];
        for(int i = leafCount - 1; i > 0; i--)
            v[i] = max(v[i * 2], v[i * 2 + 1]);
    }
    int GetMax(int a, int b) {
        a += leafCount; b += leafCount;
        int result = max(v[a], v[b]);
        for(; a / 2 != b / 2; a /= 2, b /= 2) {
            if(a % 2 == 0)
                result = max(result, v[a + 1]);
            if(b % 2 == 1)
                result = max(result, v[b - 1]);
        }
        return result;
    }
};

int Find(int x, vector<int>&f) {
    return f[x] == x ? x : f[x] = Find(f[x], f);
}

void TestCase() {
    int n, m, q; scanf("%d%d%d", &n, &m, &q);
    
    vector<int>f(n);
    vector<set<int>>s(n);
    for(int i = 0; i < n; i++) {
        f[i] = i;
        s[i].insert(i);
    }
    
    vector<int>t(n, 1 << 30);
    
    for(int i = 1; i <= m; i++) {
        int x, y; scanf("%d%d", &x, &y); x--; y--;
        x = Find(x, f); y = Find(y, f);
        if(x != y) {
            if(s[x].size() > s[y].size())
                swap(x, y);
            for(int v : s[x]) {
                if(s[y].find(v + 1) != s[y].end())
                    t[v] = min(t[v], i);
                if(s[y].find(v - 1) != s[y].end())
                    t[v - 1] = min(t[v - 1], i);
                s[y].insert(v);
            }
            s[x].clear();
            f[x] = y;
        }
    }
    
    SegTree T(t);
    for(int i = 0; i < q; i++) {
        int l, r; scanf("%d%d", &l, &r); l--; r--;
        if(l == r) {
            printf("0 ");
        } else {
            printf("%d ", T.GetMax(l, r - 1));
        }
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
