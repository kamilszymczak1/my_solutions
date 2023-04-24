#include <iostream>
#include <vector>

using namespace std;

const int inf = 999999999;

struct Tree1 {
    struct Node {
        int hi, lazy;
        Node() : hi(0), lazy(0) {}
    };
    vector<Node>nodes;
    int leafCount;
    Tree1() {}
    Tree1(int _n, int *a) {
        for(leafCount = 1; leafCount < _n; leafCount <<= 1) {}
        nodes.resize(leafCount << 1);
        for(int i = 0; i < _n; i++)
            nodes[i + leafCount].hi = a[i];
        for(int i = leafCount - 1; i; i--)
            nodes[i].hi = max(nodes[i * 2].hi, nodes[i * 2 + 1].hi);
    }
    
    void Propagate(int x) {
        nodes[x].hi += nodes[x].lazy;
        if(x < leafCount) {
            nodes[x * 2].lazy += nodes[x].lazy;
            nodes[x * 2 + 1].lazy += nodes[x].lazy;
        }
        nodes[x].lazy = 0;
    }
    
    void AddRec(int a, int b, int lo, int hi, int v, int value) {
        Propagate(v);
        if(a == lo && b == hi) {
            nodes[v].lazy += value;
            Propagate(v);
            return;
        }
        if(a >= b)
            return;
        int mid = (lo + hi) / 2;
        AddRec(a, min(b, mid), lo, mid, v * 2, value);
        AddRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
        nodes[v].hi = max(nodes[v * 2].hi, nodes[v * 2 + 1].hi);
    }
    
    int GetMaxIndexRec(int lo, int hi, int v) {
        Propagate(v);
        if(hi - lo <= 1)
            return lo;
        Propagate(v * 2);
        Propagate(v * 2 + 1);
        int mid = (lo + hi) / 2;
        if(nodes[v * 2].hi > nodes[v * 2 + 1].hi) {
            return GetMaxIndexRec(lo, mid, v * 2);
        } else {
            return GetMaxIndexRec(mid, hi, v * 2 + 1);
        }
    }
    
    void Add(int a, int b, int value) {
        AddRec(a, b, 0, leafCount, 1, value);
    }
    
    int TreeMax() {
        Propagate(1);
        return nodes[1].hi;
    }
    
    int GetMaxIndex() {
        return GetMaxIndexRec(0, leafCount, 1);
    }
    
};

struct Tree2 {
    vector<int>values;
    int leafCount;
    Tree2() {}
    Tree2(int _n) {
        for(leafCount = 1; leafCount < _n; leafCount <<= 1) {}
        values.resize(leafCount << 1, 0);
    }
    
    void Add(int x) {
        for(x += leafCount; x; x >>= 1)
            values[x]++;
    }
    
    int Sum(int a, int b) {
        a += leafCount;
        b += leafCount;
        int result = values[a];
        if(a != b)
            result += values[b];
        for(; (a >> 1) != (b >> 1); a >>= 1, b >>= 1) {
            if(!(a & 1))
                result += values[a + 1];
            if(b & 1)
                result += values[b - 1];
        }
        return result;
    }
};

Tree1 *T1;
Tree2 *T2;
int N, K;

void RemoveGrown() {
    while(T1 -> TreeMax() >= K) {
        int index = T1 -> GetMaxIndex();
        T1 -> Add(index, index + 1, -inf);
        T2 -> Add(index);
    }
}

void inicjuj(int n, int k, int *D) {
    T1 = new Tree1(n, D);
    T2 = new Tree2(n);
    N = n;
    K = k;
    RemoveGrown();
}

void podlej(int a, int b) {
    T1 -> Add(a, b + 1, 1);
    RemoveGrown();
}

int dojrzale(int a, int b) {
    return T2 -> Sum(a, b);
}
