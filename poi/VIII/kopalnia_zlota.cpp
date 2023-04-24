#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int TR = 40'001;

struct SegTree {
    struct Node {
        int sum, maxPrefix;
        Node() : sum(0), maxPrefix(0) {}
    };
    vector<Node>nodes;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        nodes.resize(leafCount * 2);
    }
    void Add(int x, int value) {
        nodes[x + leafCount].sum += value;
        nodes[x + leafCount].maxPrefix = max(0, nodes[x + leafCount].sum);
        for(x = (x + leafCount) / 2; x; x /= 2) {
            nodes[x].sum = nodes[x * 2].sum + nodes[x * 2 + 1].sum;
            nodes[x].maxPrefix = max(nodes[x * 2].maxPrefix, nodes[x * 2].sum + nodes[x * 2 + 1].maxPrefix);
        }
    }
    int MaxAll() { return nodes[1].maxPrefix; }
};

struct Event {
    int x, y, beg;
    Event(int _x, int _y, int _beg) : x(_x), y(_y), beg(_beg) {}
};

bool operator< (Event &A, Event &B) {
    if(A.x == B.x)
        return A.beg < B.beg;
    return A.x < B.x;
}

int main() {
    int w, h, n; scanf("%d%d%d", &w, &h, &n);
    vector<Event>events;
    for(int i = 0; i < n; i++) {
        int x, y; scanf("%d%d", &x, &y);
        events.emplace_back(x - w, y + TR, true);
        events.emplace_back(x + 1, y + TR, false);
    }
    SegTree T(TR * 2);
    sort(events.begin(), events.end());
    int result = 0;
    for(Event e : events) {
        T.Add(e.y - h, e.beg ? 1 : -1);
        T.Add(e.y + 1, e.beg ? -1 : 1);
        result = max(result, T.MaxAll());
    }
    printf("%d\n", result);
    return 0;
}
