#include <iostream>
#include <vector>
using namespace std;
const int MAX_N = 200007, inf = 999999999;
struct Node {
    int loBeg, hiBeg, loEnd, hiEnd;
    Node() {}
    Node(int x, int y) {
        loBeg = loEnd = min(x, y);
        hiBeg = hiEnd = max(x, y);
    }
};
class Tree {
private:
    int leafCount;
    vector<Node>nodes;
public:
    Tree(vector<pair<int, int>>&v);
    void UpdateNode(int x);
    void SwapLeaves(int a, int b);
    bool PossibleIncreasingOrder();
};
Tree::Tree(vector<pair<int, int>>&v) {
    for(leafCount = 1; leafCount < v.size(); leafCount <<= 1) {}
    nodes.resize(leafCount << 1);
    for(int i = 0; i < v.size(); i++)
        nodes[i + leafCount] = Node(v[i].first, v[i].second);
    for(int i = v.size() + leafCount; i < (leafCount << 1); i++)
        nodes[i] = Node(inf, inf);
    for(int i = leafCount - 1; i > 0; i--)
        UpdateNode(i);
}
void Tree::UpdateNode(int x) {
    int left = x << 1, right = (x << 1) + 1;
    nodes[x].loBeg = nodes[left].loBeg;
    nodes[x].hiBeg = nodes[left].hiBeg;
    if(nodes[left].loEnd != -1 && nodes[left].loEnd <= nodes[right].hiBeg)
        nodes[x].loEnd = nodes[left].loEnd <= nodes[right].loBeg ? nodes[right].loEnd : nodes[right].hiEnd;
    else
        nodes[x].loEnd = -1;
    
    if(nodes[left].hiEnd != -1 && nodes[left].hiEnd <= nodes[right].hiBeg)
        nodes[x].hiEnd = nodes[left].hiEnd <= nodes[right].loBeg ? nodes[right].loEnd : nodes[right].hiEnd;
    else
        nodes[x].hiEnd = -1;
}
void Tree::SwapLeaves(int a, int b) {
    swap(nodes[a += leafCount], nodes[b += leafCount]);
    for(a >>= 1, b >>= 1; a > 0; a >>= 1, b >>= 1) {
        UpdateNode(a);
        UpdateNode(b);
    }
}
bool Tree::PossibleIncreasingOrder() {
    return nodes[1].loEnd != -1;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m, a, b;
    cin >> n;
    vector<pair<int, int>>v;
    v.reserve(n);
    for(int i = 0; i < n; i++) {
        cin >> a >> b;
        v.emplace_back(make_pair(a, b));
    }
    Tree T(v);
    cin >> m;
    while(m--) {
        cin >> a >> b;
        T.SwapLeaves(a - 1, b - 1);
        cout << (T.PossibleIncreasingOrder() ? "TAK" : "NIE") << '\n';
    }
    return 0;
}
