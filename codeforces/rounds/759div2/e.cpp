#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

const int MAX_N = 1'000'007;

struct Query {
    int v, l, k, id;
    Query() {}
    Query(int _v, int _l, int _k, int _id) : v(_v), l(_l), k(_k), id(_id) {}
} queries[MAX_N];

bool operator< (Query &a, Query &b) {
    return a.v < b.v;
}

int n, q;
int label[MAX_N], labelCnt[MAX_N], ans[MAX_N], t[MAX_N], firstQuery[MAX_N], lastAppearance[MAX_N];
list<int>children[MAX_N], values[MAX_N];


void DFS(int x) {
    labelCnt[label[x]]++;
    t[labelCnt[label[x]]]++;
    lastAppearance[t[labelCnt[label[x]]]] = labelCnt[label[x]];
    values[labelCnt[label[x]]].push_back(label[x]);
    for(int i = firstQuery[x]; i < q && queries[i].v == x; i++) {
        Query q = queries[i];
        if(t[q.l] < q.k) {
            ans[q.id] = -1;
        } else {
            int ind = lastAppearance[t[q.l] - q.k + 1];
            while(labelCnt[values[ind].back()] != ind)
                values[ind].pop_back();
            ans[q.id] = values[ind].back() + 1;
        }
    }
    
    for(int y : children[x])
        DFS(y);
    lastAppearance[t[labelCnt[label[x]]]] = labelCnt[label[x]] - 1;
    t[labelCnt[label[x]]]--;
    labelCnt[label[x]]--;
}
void TestCase() {
    scanf("%d%d", &n, &q);
    t[0] = 0;
    for(int i = 0; i < n; i++) {
        children[i].clear();
        firstQuery[i] = 0;
    }
    values[0].clear();
    for(int i = 0; i < n; i++) {
        scanf("%d", &label[i]);
        label[i]--;
    }
    for(int i = 1; i < n; i++) {
        int x; scanf("%d", &x);
        children[x - 1].push_back(i);
    }
    for(int i = 0; i < q; i++) {
        int v, l, k; scanf("%d%d%d", &v, &l, &k);
        queries[i] = Query(v - 1, l, k, i);
        firstQuery[v]++;
    }
    sort(queries, queries + q);
    for(int i = 1; i < n; i++)
        firstQuery[i] += firstQuery[i - 1];
    DFS(0);
    for(int i = 0; i < q; i++) {
        printf("%d ", ans[i]);
    }
    putchar('\n');
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
