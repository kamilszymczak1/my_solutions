#include <cstdio>
#include <vector>

using namespace std;

class Tree {
private:
    struct Node {
        long long a, b, alazy, blazy;
        Node() : a(0), b(0), alazy(0), blazy(0) {}
        void AddLazy(long long A, long long B) {
            alazy += A;
            blazy += B;
        }
    };
    vector<Node>nodes;
    int leafCount;
    void propagate(int v, long long lo, long long hi) {
        nodes[v].a += nodes[v].alazy * (hi * (hi - 1) - lo * (lo - 1)) >> 1;
        nodes[v].b += nodes[v].blazy * (hi - lo);
        if(v < leafCount) {
            nodes[v << 1].AddLazy(nodes[v].alazy, nodes[v].blazy);
            nodes[(v << 1) + 1].AddLazy(nodes[v].alazy, nodes[v].blazy);
        }
        nodes[v].alazy = nodes[v].blazy = 0;
    }
    void add(int a, int b, int lo, int hi, int v, long long A, long long B) {
        propagate(v, lo, hi);
        if(a == lo && b == hi) {
            nodes[v].AddLazy(A, B);
            propagate(v, lo, hi);
            return;
        }
        if(a >= b)
            return;
        int mid = (lo + hi) >> 1;
        add(a, min(b, mid), lo, mid, v << 1, A, B);
        add(max(a, mid), b, mid, hi, (v << 1) + 1, A, B);
        nodes[v].a = nodes[v << 1].a + nodes[(v << 1) + 1].a;
        nodes[v].b = nodes[v << 1].b + nodes[(v << 1) + 1].b;
    }
    long long sum(int a, int b, int lo, int hi, int v) {
        propagate(v, lo, hi);
        if(a == lo && b == hi) {
            return nodes[v].a + nodes[v].b;
        }
        if(a >= b)
            return 0;
        int mid = (lo + hi) >> 1;
        long long l = sum(a, min(b, mid), lo, mid, v << 1);
        long long r = sum(max(a, mid), b, mid, hi, (v << 1) + 1);
        return l + r;
    }
public:
    Tree(int _n) {
        for(leafCount = 1; leafCount < _n; leafCount <<= 1) {}
        nodes.reserve(leafCount << 1);
        nodes.resize(leafCount << 1, Node());
    }
    void Add(int a, int b, long long A, long long B) {
        add(a, b + 1, 0, leafCount, 1, A, B);
    }
    long long Sum(int a, int b) {
        return sum(a, b + 1, 0, leafCount, 1);
    }
};

const int MAX_N = 300007;
int A[MAX_N], S[MAX_N];
int n, m;

void Insert(int x, long long s, long long a, Tree &T) {
    int d = s / a;
    T.Add(max(0, x - d), x, a, s - x * a);
    if(d > 0)
        T.Add(x + 1, min(x + d, n + 1), -a, x * a + s);
    S[x] = s;
    A[x] = a;
}

void Delete(int x, Tree &T) {
    long long s = S[x];
    long long a = A[x];
    int d = s / a;
    T.Add(max(0, x - d), x, -a, x * a - s);
    if(d > 0)
        T.Add(x + 1, min(x + d, n + 1), a, - a * x - s);
}

long long Average(int x, int y, Tree &T) {
    return T.Sum(x, y) / (y - x + 1);
}

int main() {
    scanf("%d%d", &n, &m);
    int x, y, z;
    char c;
    Tree T(n + 2);
    for(int i = 0; i < m; i++) {
        scanf(" %c", &c);
        if(c == 'U') {
            scanf("%d", &x);
            Delete(x, T);
        }
        if(c == 'P') {
            scanf("%d%d%d", &x, &y, &z);
            Insert(x, y, z, T);
        }
        if(c == 'Z') {
            scanf("%d%d", &x, &y);
            printf("%lld\n", Average(x, y, T));
        }
    }
    return 0;
}
