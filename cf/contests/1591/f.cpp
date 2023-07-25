#include <iostream>
#include <vector>

using namespace std;

const long long mod = 998244353;

struct SegTree {
    struct Node {
        int sum, lazyAdd, lazyMult;
        Node *child[2];
        Node() {
            sum = lazyAdd = 0;
            lazyMult = 1;
            child[0] = child[1] = nullptr;
        }
    };
    inline int Add(int a, int b) {
        if(a + b >= mod)
            return a + b - mod;
        return a + b;
    }
    int leafCount, a, b, value;
    Node *root;
    SegTree(int size) {
        for(leafCount = 1; leafCount < size; leafCount *= 2) {}
        root = new Node();
    }
    void Push(Node *n, int range) {
        for(int i = 0; i < 2; i++) {
            if(n -> child[i] == nullptr)
                n -> child[i] = new Node();
            n -> child[i] -> sum = (1ll * n -> child[i] -> sum * n -> lazyMult + 1ll * n -> lazyAdd * (range / 2)) % mod;
            n -> child[i] -> lazyAdd = (1ll * n -> child[i] -> lazyAdd * n -> lazyMult + n -> lazyAdd) % mod;
            n -> child[i] -> lazyMult = (1ll * n -> child[i] -> lazyMult * n -> lazyMult) % mod;
        }
        n -> lazyAdd = 0;
        n -> lazyMult = 1;
    }
    void AddRec(int lo, int hi, Node *n) {
        if(a <= lo && hi <= b) {
            n -> lazyAdd = Add(n -> lazyAdd, value);
            n -> sum = (1ll * value * (hi - lo) + n -> sum) % mod;
            return;
        }
        if(lo >= b || hi <= a)
            return;
        Push(n, hi - lo);
        const int mid = (lo + hi) / 2;
        AddRec(lo, mid, n -> child[0]);
        AddRec(mid, hi, n -> child[1]);
        n -> sum = Add(n -> child[0] -> sum, n -> child[1] -> sum);
    }
    void Add(int _a, int _b, int _value) {
        a = _a; b = _b + 1; value = _value;
        return AddRec(0, leafCount, root); 
    }
    
    void AddAll(int value) {
        root -> lazyAdd = Add(root -> lazyAdd, value);
        root -> sum = (root -> sum + 1ll * value * leafCount) % mod;
    }
    void MultRec(int lo, int hi, Node *n) {
        if(a <= lo && hi <= b) {
            n -> lazyAdd = (1ll * n -> lazyAdd * value) % mod;
            n -> lazyMult = (1ll * n -> lazyMult * value) % mod;
            n -> sum = (1ll * n -> sum * value) % mod;
            return;
        }
        if(lo >= b || hi <= a)
            return;
        Push(n, hi - lo);
        const int mid = (lo + hi) / 2;
        MultRec(lo, mid, n -> child[0]);
        MultRec(mid, hi, n -> child[1]);
        n -> sum = Add(n -> child[0] -> sum, n -> child[1] -> sum);
    }
    void Mult(int _a, int _b, int _value) {
        a = _a; b = _b + 1; value = _value;
        return MultRec(0, leafCount, root);
    }
    void MultAll(int value) {
        root -> lazyMult = (1ll * root -> lazyMult * value) % mod;
        root -> lazyAdd = (1ll * root -> lazyAdd * value) % mod;
        root -> sum = (1ll * root -> sum * value) % mod;
    }
    long long SumAll() {
        return root -> sum;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n, maxx = 0; cin >> n;
    vector<int>a(n);
    for(auto &x : a) {
        cin >> x; x--;
        maxx = max(maxx, x);
    }
    SegTree T(maxx + 1);
    T.Add(0, a[0], 1);
    for(int i = 1; i < n; i++) {
        int sum = T.SumAll();
        T.MultAll(mod - 1);
        T.Add(0, maxx, sum);
        T.Mult(a[i] + 1, maxx, 0);
    }
    cout << T.SumAll() << '\n';
    return 0;
}
