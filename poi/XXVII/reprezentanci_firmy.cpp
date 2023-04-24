#include <cstdio>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

const int MAX_N = 200'007;
const int inf = 1 << 30;

struct SegTree {
    
    vector<pair<int, int>>values;
    int leafCount;
    SegTree() {}
    SegTree(vector<int>&v) {
        for(leafCount = 1; leafCount < (int)v.size(); leafCount *= 2) {}
        values.resize(leafCount * 2, make_pair(inf, 0));
        for(int i = leafCount; i < leafCount * 2; i++)
            values[i].second = i - leafCount;
        for(int i = 0; i < v.size(); i++)
            values[i + leafCount].first = v[i];
        for(int i = leafCount - 1; i; i--)
            values[i] = min(values[i * 2], values[i * 2 + 1]);
    }
    void Disable(int x) {
        x += leafCount;
        values[x].first = inf;
        for(x /= 2; x; x /= 2)
            values[x] = min(values[x * 2], values[x * 2 + 1]);
    }
    pair<int, int> GetMin(int a, int b) {
        pair<int, int>result = min(values[a + leafCount], values[b + leafCount]);
        for(a += leafCount, b += leafCount; a / 2 != b / 2; a /= 2, b /= 2) {
            if(a % 2 == 0)
                result = min(result, values[a + 1]);
            if(b % 2 == 1)
                result = min(result, values[b - 1]);
        }
        return result;
    }
} T;

struct Requirement {
    int x, y, id, p;
    Requirement() {}
    Requirement(int _x, int _y, int _id, int _p) : x(_x), y(_y), id(_id), p(_p) {}
} r[MAX_N];

int taken[MAX_N], inAnswer[MAX_N], totalCount = 0;
long long totalSum = 0;
vector<int>children[MAX_N];

bool operator<(Requirement &A, Requirement &B) {
    if(A.x == B.x)
        return A.y > B.y;
    return A.x < B.x;
}

void DFS(int x) {
    for(int y : children[x]) {
        DFS(y);
        taken[x] += taken[y];
    }
    while(taken[x] < r[x].p) {
        pair<int, int>p = T.GetMin(r[x].x, r[x].y);
        totalSum += p.first;
        T.Disable(p.second);
        inAnswer[p.second] = 1;
        taken[x]++;
        totalCount++;
    }
}

int main() {
    int n; scanf("%d", &n);
    vector<int>c(n);
    for(int &x : c)
        scanf("%d", &x);
    T = SegTree(c);
    int m; scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int x, y, p; scanf("%d%d%d", &x, &y, &p);
        r[i] = Requirement(x - 1, y - 1, i, p);
    }
    sort(r, r + m);
    for(int i = 0; i < m; i++)
        r[i].id = i;
    stack<Requirement>s;
    vector<int>roots;
    for(int i = 0; i < m; i++) {
        while(!s.empty() && s.top().y < r[i].x)
            s.pop();
        if(!s.empty()) {
            children[s.top().id].push_back(r[i].id);
        } else {
            roots.push_back(r[i].id);
        }
        s.push(r[i]);
    }
    for(int root : roots)
        DFS(root);
    printf("%lld\n%d\n", totalSum, totalCount);
    for(int i = 0; i < n; i++) {
        if(inAnswer[i] == 1) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    return 0;
}
