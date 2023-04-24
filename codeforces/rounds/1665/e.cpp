#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int B = 31;

struct SegTree {
    vector<array<int, B>>v;
    int leafCount;
    void Merge(array<int, B>a, array<int, B>&b, array<int, B>&c) {
        int i = 0, j = 0;
        for(int k = 0; k < B; k++) {
            if(a[i] < b[j]) {
                c[k] = a[i];
                i++;
            } else {
                c[k] = b[j];
                j++;
            }
        }
    }
    SegTree(vector<int>&a) {
        int n = a.size();
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        v.resize(leafCount * 2);
        for(int i = 0; i < leafCount * 2; i++)
            fill(v[i].begin(), v[i].end(), 1 << 30);
        for(int i = 0; i < n; i++)
            v[i + leafCount][0] = a[i];
        for(int i = leafCount - 1; i > 0; i--)
            Merge(v[i * 2], v[i * 2 + 1], v[i]);
    }
    array<int, B> Query(int l, int r) {
        l += leafCount; r += leafCount;
        array<int, B>result = v[l];
        if(r != l)
            Merge(result, v[r], result);
        for(; l / 2 != r / 2; l /= 2, r /= 2) {
            if(l % 2 == 0)
                Merge(result, v[l + 1], result);
            if(r % 2 == 1)
                Merge(result, v[r - 1], result);
        }
        return result;
    }
};

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(int &x : a)
        scanf("%d", &x);
    SegTree T(a);
    int qq; scanf("%d", &qq);
    for(int i = 0; i < qq; i++) {
        int l, r; scanf("%d%d", &l, &r); l--; r--;
        array<int, B>v = T.Query(l, r);
        int result = 1 << 30;
        for(int i = 0; i < B; i++) {
            for(int j = i + 1; j < B; j++) {
                result = min(result, v[i] | v[j]);
            }
        }
        printf("%d\n", result);
    }
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
