#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

struct Query {
    int type, s, x, y;
    Query(int _type, int _s, int _x, int _y) : type(_type), s(_s), x(_x), y(_y) {}
    Query() {}
};

struct SegTree {
    struct Node {
        int lMin, rMin, allMin;
        Node() : lMin(1 << 29), rMin(1 << 29), allMin(1 << 30) {}
    };
    vector<Node>nodes;
    vector<multiset<int>>sL, sR;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        nodes.resize(leafCount * 2);
        sL.resize(leafCount);
        sR.resize(leafCount);
        for(int i = 0; i < leafCount; i++) {
            sL[i].insert(1 << 29);
            sR[i].insert(1 << 29);
        }
    }
    void Merge(int i) {
        nodes[i].lMin = min(nodes[i * 2].lMin, nodes[i * 2 + 1].lMin);
        nodes[i].rMin = min(nodes[i * 2].rMin, nodes[i * 2 + 1].rMin);
        nodes[i].allMin = min(nodes[i * 2].allMin, nodes[i * 2 + 1].allMin);
        nodes[i].allMin = min(nodes[i].allMin, nodes[i * 2].rMin + nodes[i * 2 + 1].lMin);
    }
    void InsertL(int k, int x) {
        sL[k].insert(x);
        nodes[k + leafCount].lMin = *sL[k].begin();
        nodes[k + leafCount].allMin = nodes[k + leafCount].lMin + nodes[k + leafCount].rMin;
        for(k = (k + leafCount) / 2; k; k /= 2)
            Merge(k);
    }
    void InsertR(int k, int x) {
        sR[k].insert(x);
        nodes[k + leafCount].rMin = *sR[k].begin();
        nodes[k + leafCount].allMin = nodes[k + leafCount].lMin + nodes[k + leafCount].rMin;
        for(k = (k + leafCount) / 2; k; k /= 2)
            Merge(k);
    }
    void DeleteL(int k, int x) {
        sL[k].erase(sL[k].find(x));
        nodes[k + leafCount].lMin = *sL[k].begin();
        nodes[k + leafCount].allMin = nodes[k + leafCount].lMin + nodes[k + leafCount].rMin;
        for(k = (k + leafCount) / 2; k; k /= 2)
            Merge(k);
    }
    void DeleteR(int k, int x) {
        sR[k].erase(sR[k].find(x));
        nodes[k + leafCount].rMin = *sR[k].begin();
        nodes[k + leafCount].allMin = nodes[k + leafCount].lMin + nodes[k + leafCount].rMin;
        for(k = (k + leafCount) / 2; k; k /= 2)
            Merge(k);
    }
    int GetMin() { return nodes[1].allMin; }
};

void Solve(vector<Query>&queries, vector<int>&result) {
    
    vector<int>values;
    for(Query &q : queries) {
        values.emplace_back(q.y - q.x);
        values.emplace_back(q.x - q.y);
    }
    sort(values.begin(), values.end());
    values.resize(unique(values.begin(), values.end()) - values.begin());
    
    SegTree T(values.size());
    for(int i = 0; i < (int)queries.size(); i++) {
        int x = queries[i].x, y = queries[i].y;
        if(queries[i].s == 1) {
            int index = lower_bound(values.begin(), values.end(), x - y) - values.begin();
            if(queries[i].type == 1)
                T.InsertL(index, x);
            else
                T.DeleteL(index, x);
        } else {
            int index = lower_bound(values.begin(), values.end(), y - x) - values.begin();
            if(queries[i].type == 1)
                T.InsertR(index, x);
            else
                T.DeleteR(index, x);
        }
        result[i] = min(result[i], T.GetMin());
    }
}

int main() {
    
    int q; scanf("%d", &q);
    
    vector<int>result(q, 1 << 29);
    vector<Query>queries(q);
    for(int i = 0; i < q; i++) {
        int type, s, x, y; scanf("%d%d%d%d", &type, &s, &x, &y);
        queries[i] = Query(type, s, x, y);
    }
    
    Solve(queries, result);
    for(int i = 0; i < q; i++)
        swap(queries[i].x, queries[i].y);
    Solve(queries, result);
    
    for(auto x : result) {
        if(x > 500'000) {
            printf("-1\n");
        } else {
            printf("%d\n", x);
        }
    }
    
    return 0;
}
