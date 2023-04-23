#include <iostream>
#define inf 100000

using namespace std;

struct Node {
    int max, sum;
};

const int leafCount = 65536;
const int treeSize = leafCount * 2;
Node tree[treeSize];

void update(int a, int b, int u, int lo, int hi, int val);
int getMax(int a, int b, int u, int lo, int hi);

int main() {
    ios_base::sync_with_stdio(0);
    int n, m, z, p, k, l;
    cin >> n >> m >> z;
    for(int i = 0; i < z; i++) {
        cin >> p >> k >> l;
        if(getMax(p - 1, k - 1, 1, 0, leafCount) + l <= m) {
            cout << "T\n";
            update(p - 1, k - 1, 1, 0, leafCount, l);
        } else cout << "N\n";
    }
    return 0;
}

void update(int a, int b, int u, int lo, int hi, int val) {
    if(a == lo && b == hi) {
        tree[u].max += val;
        tree[u].sum += val;
        return;
    }
    if(b <= a) return;
    int mid = (lo + hi) / 2;
    update(a, min(b, mid), u * 2, lo, mid, val);
    update(max(a, mid), b, u * 2 + 1, mid, hi, val);
    tree[u].max = max(tree[u * 2].max, tree[u * 2 + 1].max) + tree[u].sum;
}

int getMax(int a, int b, int u, int lo, int hi) {
    if(a == lo && b == hi) return tree[u].max;
    if(b <= a) return -inf;
    int mid = (lo + hi) / 2;
    int leftMax = getMax(a, min(b, mid), u * 2, lo, mid);
    int rightMax = getMax(max(a, mid), b, u * 2 + 1, mid, hi);
    return max(leftMax,rightMax) + tree[u].sum;
}
