#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct SegTree {
    struct Node {
        int value, lazyAdd, lazySet;
        Node() : value(0), lazyAdd(0), lazySet(0) {}
    };
    vector<Node>nodes;
    int leafCount;
    SegTree(int _n) {
        for(leafCount = 1; leafCount < _n; leafCount *= 2) {}
        nodes.reserve(leafCount * 2);
        nodes.resize(leafCount * 2);
    }
    void Propagate(int x) {
        nodes[x].value = max(nodes[x].lazySet, nodes[x].value) + nodes[x].lazyAdd;
        if(x < leafCount) {
            if(nodes[x].lazySet == 0) {
                nodes[x * 2].lazyAdd += nodes[x].lazyAdd;
                nodes[x * 2 + 1].lazyAdd += nodes[x].lazyAdd;
            } else {
                nodes[x * 2].lazySet = nodes[x].lazySet + nodes[x].lazyAdd;
                nodes[x * 2].lazyAdd = 0;
                nodes[x * 2 + 1].lazySet = nodes[x].lazySet + nodes[x].lazyAdd;
                nodes[x * 2 + 1].lazyAdd = 0;
            }
        }
        nodes[x].lazySet = nodes[x].lazyAdd = 0;
    }
    void Add(int a, int b, int lo, int hi, int x, int value) {
        Propagate(x);
        if(a == lo && b == hi) {
            nodes[x].lazyAdd += value;
            Propagate(x);
            return;
        }
        if(a >= b)
            return;
        int mid = (lo + hi) / 2;
        Add(a, min(b, mid), lo, mid, x * 2, value);
        Add(max(a, mid), b, mid, hi, x * 2 + 1, value);
        nodes[x].value = max(nodes[x * 2].value, nodes[x * 2 + 1].value);
    }
    void Add(int a, int b, int value) {
        Add(a, b + 1, 0, leafCount, 1, value);
    }
    void Set(int a, int b, int lo, int hi, int x, int value) {
        Propagate(x);
        if(a == lo && b == hi) {
            nodes[x].lazySet = value;
            nodes[x].lazyAdd = 0;
            Propagate(x);
            return;
        }
        if(a >= b)
            return;
        int mid = (lo + hi) / 2;
        Set(a, min(b, mid), lo, mid, x * 2, value);
        Set(max(a, mid), b, mid, hi, x * 2 + 1, value);
        nodes[x].value = max(nodes[x * 2].value, nodes[x * 2 + 1].value);
    }
    void Set(int a, int b, int value) {
        Set(a, b + 1, 0, leafCount, 1, value);
    }
    int GetMax(int a, int b, int lo, int hi, int x) {
        Propagate(x);
        if(a == lo && b == hi)
            return nodes[x].value;
        if(a >= b)
            return 0;
        int mid = (lo + hi) / 2;
        int L = GetMax(a, min(b, mid), lo, mid, x * 2);
        int R = GetMax(max(a, mid), b, mid, hi, x * 2 + 1);
        return max(L, R);
    }
    int GetMax(int a, int b) {
        return GetMax(a, b + 1, 0, leafCount, 1);
    }
};

int Scale(vector<int>&h, vector<vector<pair<int, bool>>>&req) {
    vector<int>allH;
    for(int x : h)
        allH.push_back(x);
    for(vector<pair<int, bool>>&vec : req)
        for(pair<int, bool>&p : vec)
            allH.push_back(p.first);
    sort(allH.begin(), allH.end());
    map<int, int>m;
    int current = 0;
    for(int i = 0; i < allH.size(); i++) {
        while(i < allH.size() - 1 && allH[i] == allH[i + 1])
            i++;
        m[allH[i]] = current++;
    }
    for(int &x : h)
        x = m[x];
    for(vector<pair<int, bool>>&vec : req)
        for(pair<int, bool>&p : vec)
            p.first = m[p.first];
    return current;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, q; cin >> n >> q;
    vector<int>h(n, 0);
    vector<vector<pair<int, bool>>>req(n); //0 - wet 1 - dry
    
    for(int i = 1; i < n; i++) {
        cin >> h[i];

    }
    
    for(int i = 0; i < q; i++) {
        int x, w, s; cin >> x >> w >> s;
        req[x - 1].emplace_back(w, s);
    }
    
    int height = Scale(h, req);
    
    SegTree T(height + 3);
    
    for(int i = 0; i < n; i++) {
        int hi = T.GetMax(0, h[i]);
        T.Set(0, h[i], hi);
        for(pair<int, bool>p : req[i]) {
            if(p.second == 0) {
                T.Add(0, p.first - 1, 1);
            } else {
                T.Add(p.first, height + 2, 1);
            }
        }
    }
    
    cout << T.GetMax(0, height + 2) << '\n';
    
    return 0;
}
