#include <algorithm>
#include <iostream>

using namespace std;
const long long inf = 1ll << 60;
const int MAX_N = 300007;
const int leafCount = 1 << 19;
struct Node {
    long long value, lazy;
    Node() : value(0), lazy(0) {}
} nodes[leafCount << 1];
long long p[leafCount << 1], n, q, f = 0;

void Propagate(int v) {
    nodes[v].value += nodes[v].lazy;
    if(v < leafCount) {
        nodes[v * 2].lazy += nodes[v].lazy;
        nodes[v * 2 + 1].lazy += nodes[v].lazy;
    }
    nodes[v].lazy = 0;
}

void TreeAdd(int a, int b, long long value, int lo = 0, int hi = leafCount, int v = 1) {
    if(a == lo && b == hi) {
        nodes[v].lazy += value;
        Propagate(v);
        return;
    }
    Propagate(v);
    if(a >= b)
        return;
    int mid = (lo + hi) / 2;
    TreeAdd(a, min(b, mid), value, lo, mid, v * 2);
    TreeAdd(max(a, mid), b, value, mid, hi, v * 2 + 1);
    nodes[v].value = max(nodes[v * 2].value, nodes[v * 2 + 1].value);
}

long long TreeGetMax(int a, int b, int lo = 0, int hi = leafCount, int v = 1) {
    Propagate(v);
    if(a == lo && b == hi)
        return nodes[v].value;
    if(a >= b)
        return -inf;
    int mid = (lo + hi) / 2;
    long long l = TreeGetMax(a, min(b, mid), lo, mid, v * 2);
    long long r = TreeGetMax(max(a, mid), b, mid, hi, v * 2 + 1);
    return max(l, r);
}

long long PointValue(int x) {
    long long result = 0;
    for(x += leafCount; x; x >>= 1)
        result += p[x];
    return result;
}

void PrefixAdd(int x, long long value) {
    p[x + leafCount] += value;
    for(x += leafCount; x; x >>= 1) {
        if(x & 1)
            p[x - 1] += value;
    }
}

void SuffixAdd(int x, long long value) {
    p[x + leafCount] += value;
    for(x += leafCount; x; x >>= 1) {
        if(!(x & 1))
            p[x + 1] += value;
    }
}


void Add(long long x, long long y) {
    int beg = 0, end = n - 1;
    while(beg <= end) {
        long long mid = (beg + end) / 2;
        if(PointValue(mid) + mid - n >= x) {
            end = mid - 1;
        } else {
            beg = mid + 1;
        }
    }
    if(end + 1 < n) {
        TreeAdd(end + 1, n, y);
        SuffixAdd(end + 1, y);
    }
        
}

void Subtract(long long x, long long y) {
    int beg = 0, end = n - 1;
    while(beg <= end) {
        long long mid = (beg + end) / 2;
        if(PointValue(mid) + mid - n <= x) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    if(beg > 0) {
        TreeAdd(0, beg, -y);
        PrefixAdd(beg - 1, -y);
    }
}

int Query() {
    while(f < n - 1 && PointValue(f) + f < TreeGetMax(f + 1, n))
        f++;
    return n - f;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) {
        cin >> p[i + leafCount];
    }
    sort(p + leafCount, p + leafCount + n);
    for(int i = 0; i < n; i++) {
        p[i + leafCount] += n - i;
        nodes[i + leafCount].value = p[i + leafCount];
    }
    
    for(int i = leafCount - 1; i; i--)
        nodes[i].value = max(nodes[i * 2].value, nodes[i * 2 + 1].value);
    
    while(q--) {
        long long x, y;
        char type;
        cin >> type;
        if(type == 'B') {
            cin >> x >> y;
            Add(x, y);
        } else if(type == 'K') {
            cin >> x >> y;
            Subtract(x, y);
        } else {
            cout << Query() << '\n';
        }
        
    }
    
    return 0;
}
