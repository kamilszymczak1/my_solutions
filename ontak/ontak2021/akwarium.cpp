#include <iostream>
#include <vector>

using namespace std;

struct SegTree {
    struct Node {
        int value, lazySet, lazyAdd;
        Node *left, *right;
        Node() {
            value = lazySet = lazyAdd = 0;
            left = right = NULL;
        }
    };
    Node *root;
    int leafCount;
    SegTree(int _width) {
        for(leafCount = 1; leafCount < _width; leafCount *= 2) {}
        root = new Node();
    }
    void Propagate(Node *node, int lo, int hi) {
        if(node -> lazySet != 0) {
            node -> value = node -> lazySet;
        }
        node -> value += node -> lazyAdd;
        if(hi - lo != 1) {
            if(node -> left == NULL) {
                node -> left = new Node();
            }
            if(node -> right == NULL) {
                node -> right = new Node();
            }
            if(node -> lazySet != 0) {
                node -> left -> lazySet = node -> lazySet + node -> lazyAdd;
                node -> left -> lazyAdd = 0;
                node -> right -> lazySet = node -> lazySet + node -> lazyAdd;
                node -> right -> lazyAdd = 0;
            } else {
                node -> left -> lazyAdd += node -> lazyAdd;
                node -> right -> lazyAdd += node -> lazyAdd;
            }
            
        }
        node -> lazySet = 0;
        node -> lazyAdd = 0;
    }
    
    int GetMax(int a, int b, int lo, int hi, Node *node) {
        Propagate(node, lo, hi);
        if(a == lo && b == hi)
            return node -> value;
        if(a >= b)
            return 0;
        int mid = (lo + hi) / 2;
        int L = GetMax(a, min(b, mid), lo, mid, node -> left);
        int R = GetMax(max(a, mid), b, mid, hi, node -> right);
        return max(L, R);
    }
    
    int GetMax(int a, int b) {
        return GetMax(a, b + 1, 0, leafCount, root);
    }
    
    void SetMax(int a, int b, int lo, int hi, Node *node, int value) {
        if(a >= b)
            return;
        if(a == lo && b == hi) {
            node -> lazySet = value;
            node -> lazyAdd = 0;
            return;
        }
        Propagate(node, lo, hi);
        int mid = (lo + hi) / 2;
        SetMax(a, min(b, mid), lo, mid, node -> left, value);
        SetMax(max(a, mid), b, mid, hi, node -> right, value);
        node -> value = 0;
        if(node -> left != NULL)
            node -> value = max(node -> value, max(node -> left -> value, node -> left -> lazySet) + node -> left -> lazyAdd);
        if(node -> right != NULL)
            node -> value = max(node -> value, max(node -> right -> value, node -> right -> lazySet) + node -> right -> lazyAdd);
    }
    
    void SetMax(int a, int b, int value) {
        SetMax(a, b + 1, 0, leafCount, root, value);
    }
    
    void Add(int a, int b, int lo, int hi, Node *node, int value) {
        if(a >= b)
            return;
        if(a == lo && b == hi) {
            node -> lazyAdd += value;
            return;
        }
        Propagate(node, lo, hi);
        int mid = (lo + hi) / 2;
        Add(a, min(b, mid), lo, mid, node -> left, value);
        Add(max(a, mid), b, mid, hi, node -> right, value);
        node -> value = 0;
        if(node -> left != NULL)
            node -> value = max(node -> value, max(node -> left -> value, node -> left -> lazySet) + node -> left -> lazyAdd);
        if(node -> right != NULL)
            node -> value = max(node -> value, max(node -> right -> value, node -> right -> lazySet) + node -> right -> lazyAdd);
    }
    
    void Add(int a, int b, int value) {
        Add(a, b + 1, 0, leafCount, root, value);
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n, q, maxH = 0; cin >> n >> q;
    vector<int>h(n, 0);
    for(int i = 1; i < n; i++) {
        cin >> h[i];
        maxH = max(maxH, h[i]);
    }
    vector<vector<pair<int, bool>>>req(n); //[w, s] s = 0 -> dry, s = 1 -> wet
    for(int i = 0; i < q; i++) {
        int x, w, s; cin >> x >> w >> s;
        req[x - 1].emplace_back(w, s);
        maxH = max(maxH, w);
    }
    
    SegTree T(maxH + 2);
    
    for(int i = 0; i < n; i++) {
        int m = T.GetMax(0, h[i]);
        T.SetMax(0, h[i], m);
        for(pair<int, bool>&p : req[i]) {
            if(p.second == 0) {
                T.Add(0, p.first - 1, 1);
            } else {
                T.Add(p.first, maxH + 1, 1);
            }
        }
    }
    
    cout << T.GetMax(0, maxH + 1) << '\n';
    return 0;
}

/*
5 7
3 2 4 3
3 2 1
2 2 0
4 4 1
5 2 0
3 3 1
1 2 1
2 3 0
*/
