#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 60;

// int floor(int x, int y) { return x / y; }
// int ceil(int x, int y) { return x % y == 0 ? x / y : x / y + 1; };
// 
// 
// struct SegTree {
//     struct Node {
//         long long value, lazy;
//         Node() : value(0), lazy(0) {}
//     };
//     vector<Node>nodes;
//     int leafCount;
//     SegTree(int n) {
//         for(leafCount = 1; leafCount < n; leafCount *= 2) {}
//         nodes.resize(leafCount * 2);
//     }
//     void Propagate(int v) {
//         for(int i = 0; i < 2; i++) {
//             nodes[v * 2 + i].value += nodes[v].lazy;
//             nodes[v * 2 + i].lazy += nodes[v].lazy;
//         }
//         nodes[v].lazy = 0;
//     }
//     void Add(int a, int b, long long value) {
//         AddRec(a, b + 1, 0, leafCount, 1, value);
//     }
//     void AddRec(int a, int b, int lo, int hi, int v, long long value) {
//         if(a == lo && b == hi) {
//             nodes[v].value += value;
//             nodes[v].lazy += value;
//             return;
//         }
//         if(a >= b)
//             return;
//         int mid = (lo + hi) / 2;
//         Propagate(v);
//         AddRec(a, min(b, mid), lo, mid, v * 2, value);
//         AddRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
//         nodes[v].value = nodes[v * 2].value + nodes[v * 2 + 1].value;
//     }
//     int Max(int a, int b) {
//         return MaxRec(a, b + 1, 0, leafCount, 1);
//     }
//     void MaxRec(int a, int b, int lo, int hi, int v, long long value) {
//         if(a == lo && b == hi) {
//             return nodes[v].value;
//         }
//         if(a >= b)
//             return -inf;
//         int mid = (lo + hi) / 2;
//         Propagate(v, lo, hi);
//         long long L = MaxRec(a, min(b, mid), lo, mid, v * 2, value);
//         long long R = MaxRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
//         return max(L, R);
//     }
// };

bool CheckMin(int m, vector<int>&x, int l) {
    int n = x.size(), last = 0;
    for(int i = 0; i < n - 1; i++) {
        if(x[i + 1] - last < m)
            return false;
        last = max(x[i], last + m);
    }
    return l - last >= m;
}

bool CheckMax(int m, vector<int>&x, int l) {
    int n = x.size(), last = 0;
    for(int i = 0; i < n - 1; i++) {
        if(x[i] - last > m)
            return false;
        last = min(x[i + 1], last + m);
    }
    return l - last <= m;
}

int main() {
    int l, n; scanf("%d%d", &l, &n);
    vector<int>x(n);
    for(auto &y : x)
        scanf("%d", &y);
    
    if(n == 1) {
        printf("0 %d\n", l);
        return 0;
    }
    
    int lo = 0, hi = (1 << 30) - 1;
    for(int i = 29; i >= 0; i--) {
        lo += 1 << i;
        if(CheckMin(lo, x, l) == false)
            lo -= 1 << i;
        hi -= 1 << i;
        if(CheckMax(hi, x, l) == false)
            hi += 1 << i;
    }
    
    vector<int>a(n + 1), c(n + 1);
    a[n] = c[n] = l;
    for(int i = 1; i <= n - 1; i++)
        a[i] = max(x[i - 1], a[i - 1] + lo);
    
    
    for(int i = n - 1; i >= 0; i--) {
        int y = min(c[i + 1] - a[i], hi);
        c[i] = c[i + 1] - y;
    }
    
    for(int i = 1; i <= n; i++)
        printf("%d %d\n", c[i - 1], c[i]);
    
    return 0;
}
