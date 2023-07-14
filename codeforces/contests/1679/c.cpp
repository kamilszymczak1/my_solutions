#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <bitset>

using namespace std;

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int _n) {
        for(leafCount = 1; leafCount < _n; leafCount *= 2) {}
        values.resize(leafCount * 2);
    }
    void Add(int x, int value) {
        x += leafCount;
        values[x] += value;
        for(x /= 2; x; x /= 2)
            values[x] = min(values[x * 2], values[x * 2 + 1]);
        
    }
    int GetMin(int a, int b) {
        a += leafCount;
        b += leafCount;
        int ans = min(values[a], values[b]);
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                ans = min(ans, values[a + 1]);
            if(b % 2 == 1)
                ans = min(ans, values[b - 1]);
            a /= 2;
            b /= 2;
        }
        return ans;
    }
};

void TestCase() {
    int n, q; scanf("%d%d", &n, &q);
    
    SegTree A(n), B(n);
    for(int i = 0; i < q; i++) {
        int t; scanf("%d", &t);
        if(t == 1) {
            int x, y; scanf("%d%d", &x, &y);
            A.Add(x - 1, 1);
            B.Add(y - 1, 1);
        } else if(t == 2) {
            int x, y; scanf("%d%d", &x, &y);
            A.Add(x - 1, -1);
            B.Add(y - 1, -1);
        } else {
            int x1, y1, x2, y2; scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            bool ans = false;
            if(A.GetMin(x1 - 1, x2 - 1) > 0)
                ans = true;
            if(B.GetMin(y1 - 1, y2 - 1) > 0)
                ans = true;
            printf("%s\n", ans ? "Yes" : "No");
        }
    }
}

int main() {
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
