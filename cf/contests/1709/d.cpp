#include <cstdio>
#include <vector>
#include <algorithm>
#include <bitset>
#include <set>
#include <queue>
#include <stack>
#include <cstring>
#include <cmath>

using namespace std;

struct SegTree {
    vector<int>v;
    int leafCount;
    SegTree(vector<int>a) {
        int n = a.size();
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        v.resize(leafCount * 2);
        for(int i = 0; i < n; i++)
            v[i + leafCount] = a[i];
        for(int i = leafCount - 1; i > 0; i--)
            v[i] = max(v[i * 2], v[i * 2 + 1]);
    }
    int GetMax(int a, int b) {
        a += leafCount;
        b += leafCount;
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

void TestCase() {
    int n, m; scanf("%d%d", &n, &m);
    vector<int>a(m);
    for(auto &x : a)
        scanf("%d", &x);
    SegTree T(a);
    
    int q; scanf("%d", &q);
    while(q--) {
        int r1, c1, r2, c2; scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
        int k; scanf("%d", &k);
        
        if(abs(r1 - r2) % k != 0 || abs(c1 - c2) % k != 0) {
            printf("NO\n");
            continue;
        }
        
        int p = (n - r1) / k;
        int maxRow = r1 + p * k;
        
        if(c1 > c2)
            swap(c1, c2);
        c1--; c2--;
        if(T.GetMax(c1, c2) < maxRow) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
