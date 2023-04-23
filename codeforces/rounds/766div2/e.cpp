#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

struct Edge {
    int a, b, w;
    Edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w) {}
};

struct Node {
    vector<Edge>next;
    int row, column;
    long long dist;
    Node(int _row, int _column) {
        row = _row; column = _column;
        dist = 1ll << 61;
    }
};

bool cmp(Node &a, Node &b) {
    if(a.row == b.row)
        return a.column < b.column;
    return a.row < b.row;
}

void TestCase() {
    vector<Node>nodes;
    int n, m, k; cin >> n >> m >> k;
    vector<int>x(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> x[i];
    for(int i = 0; i < k; i++) {
        int a, b, c, d, h;
        cin >> a >> b >> c >> d >> h;
        nodes.push_back(Node(a, b));
        nodes.back().next.push_back(Edge(c, d, -h));
        nodes.push_back(Node(c, d));
    }
    nodes.push_back(Node(1, 1));
    nodes.push_back(Node(n, m));
    sort(nodes.begin(), nodes.end(), cmp);
    vector<Node>newNodes;
    int z = nodes.size();
    for(int i = 0; i < z; i++) {
        newNodes.push_back(Node(nodes[i].row, nodes[i].column));
        for(Edge e : nodes[i].next)
            newNodes.back().next.push_back(e);
        newNodes.push_back(nodes[i]);
        while(i < z - 1 && nodes[i].row == nodes[i + 1].row && nodes[i].column == nodes[i + 1].column) {
            i++;
            for(Edge e : nodes[i].next)
                newNodes.back().next.push_back(e);
        }
    }
    swap(nodes, newNodes);
    z = nodes.size();
    nodes[0].dist = 0;
    int indexL = 0;
    for(int r = 1; r <= n; r++) {
        if(nodes[indexL].row > r)
            continue;
        int indexR = indexL, reachable = nodes[indexL].dist != (1ll << 61);
        while(indexR < z - 1 && nodes[indexR].row == nodes[indexR + 1].row) {
            indexR++;
            reachable |= nodes[indexR].dist != (1ll << 61);
        }
        if(reachable) {
            for(int j = indexL + 1; j <= indexR; j++) {
                long long xDiff = nodes[j].column - nodes[j - 1].column;
                nodes[j].dist = min(nodes[j].dist, nodes[j - 1].dist + x[r] * xDiff);
            }
            for(int j = indexR - 1; j >= indexL; j--) {
                long long xDiff = nodes[j + 1].column - nodes[j].column;
                nodes[j].dist = min(nodes[j].dist, nodes[j + 1].dist + x[r] * xDiff);
            }
            for(int j = indexL; j <= indexR; j++) {
                for(Edge e : nodes[j].next) {
                    int index = j;
                    for(int bit = 18; bit >= 0; bit--) {
                        index += 1 << bit;
                        if(index >= z || (nodes[index].row > e.a) || (nodes[index].row == e.a && nodes[index].column > e.b))
                            index -= 1 << bit;
                    }
                    nodes[index].dist = min(nodes[index].dist, nodes[j].dist + e.w);
                }
            }
        }
        indexL = indexR + 1;
    }
    if(nodes.back().dist == (1ll << 61)) {
        cout << "NO ESCAPE\n";
    } else {
        cout << nodes.back().dist  << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
