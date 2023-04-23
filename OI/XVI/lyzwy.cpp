#include <iostream>
#include <vector>

using namespace std;

struct PSOMSTree {
    struct Node {
        long long sum, maxLeft, maxRight, totalMax;
        Node(long long _x) : sum(_x), maxLeft(_x), maxRight(_x), totalMax(_x) {}
    };
    Node Merge(Node left, Node right) {
        Node result(0);
        result.sum = left.sum + right.sum;
        result.totalMax = max(left.maxRight + right.maxLeft, max(left.totalMax, right.totalMax));
        result.maxLeft = max(left.maxLeft, right.maxLeft + left.sum);
        result.maxRight = max(right.maxRight, left.maxRight + right.sum);
        return result;
    }
    vector<Node>nodes;
    int leafCount;
    PSOMSTree(int _n, long long defaultValue) {
        for(leafCount = 1; leafCount < _n; leafCount *= 2) {}
        nodes.resize(leafCount * 2, Node(defaultValue));
        for(int i = leafCount - 1; i; i--) {
            nodes[i] = Merge(nodes[i * 2], nodes[i * 2 + 1]);
        }
    }
    
    void Add(int x, long long value) {
        nodes[x + leafCount] = Node(nodes[x + leafCount].sum + value);
        for(x = (x + leafCount) / 2; x; x /= 2)
            nodes[x] = Merge(nodes[x * 2], nodes[x * 2 + 1]);
    }
    long long Max() {
        return nodes[1].totalMax;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n, m, k, d; cin >> n >> m >> k >> d;
    
    PSOMSTree T(n, -k);
    
    for(int i = 0; i < m; i++) {
        int r, x; cin >> r >> x;
        T.Add(r - 1, x);
        if(T.Max() <= (long long)d * k) {
            cout << "TAK\n";
        } else {
            cout << "NIE\n";
        }
    }
    
    
    return 0;
}
