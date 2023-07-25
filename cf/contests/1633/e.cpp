#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct Edge {
    int a, b, w;
    Edge(int _a, int _b, int _w) {
        w = _w;
        a = min(_a, _b);
        b = max(_a, _b);
    }
};

int Abs(int x) {
    if(x >= 0)
        return x;
    return -x;
}

int offset = 0;

bool operator<(Edge a, Edge b) {
    if(a.w == b.w) {
        if(a.a == b.a)
            return a.b < b.b;
        return a.a < b.a;
    }
    return Abs(offset - a.w) < Abs(offset - b.w);
}

bool operator==(Edge a, Edge b) {
    return Abs(offset - a.w) == Abs(offset - b.w) && a.a == b.a && a.b == b.b;
}

int ceil(int a, int b) {
    if(a % b == 0)
        return a / b;
    return a / b + 1;
}

struct DSU {
    vector<int>f;
    DSU(int n) {
        f.resize(n);
        for(int i = 0; i < n; i++)
            f[i] = i;
    }
    int Find(int x) {
        return f[x] == x ? x : f[x] = Find(f[x]);
    }
    void Union(int x, int y) {
        f[Find(x)] = Find(y);
    }
};

int MST(vector<Edge>&edges, int n, vector<Edge>&taken) {
    int result = 0;
    DSU dsu(n);
    for(Edge e : edges) {
        if(dsu.Find(e.a) != dsu.Find(e.b)) {
            dsu.Union(e.a, e.b);
            result += Abs(offset - e.w);
            taken.push_back(e);
        }
    }
    return result;
}

void CalcAtPoints(vector<int>points, vector<Edge>&taken, long long &result) {
    offset = 0;
    sort(taken.begin(), taken.end());
    long long slope = -(int)taken.size();
    long long value = 0, position = 0, takenId = -1;
    for(int i = 0; i < (int)taken.size(); i++)
        value += taken[i].w;
    
    for(int q : points) {
        while(takenId < (int)taken.size() - 1 && taken[takenId + 1].w < q) {
            takenId++;
            value = value + slope * (taken[takenId].w - position);
            slope += 2;
            position = taken[takenId].w;
        }
        result ^= value + slope * (q - position);
    }
}

void TestCase() {
    vector<Edge>edges;
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w;
        edges.emplace_back(x - 1, y - 1, w);
    }
    vector<int>queries;
    
    long long p, k, a, b, c, q;
    cin >> p >> k >> a >> b >> c;
    for(int i = 0; i < p; i++) {
        cin >> q; queries.push_back(q);
    }
    for(int i = 0; i < k - p; i++) {
        q = (q * a + b) % c;
        queries.push_back(q);
    }
    sort(queries.begin(), queries.end());
    offset = 0;
    sort(edges.begin(), edges.end());
    vector<int>intervals;
    for(int i = 0; i < m; i++) {
        for(int j = i + 1; j < m; j++) {
            intervals.push_back((edges[i].w + edges[j].w) / 2);
            intervals.push_back((edges[i].w + edges[j].w) / 2 + 1);
        }
    }
    sort(intervals.begin(), intervals.end());
    intervals.push_back(1e8 + 7);
    long long result = 0, queryId = 0, current = -1;
    for(int x : intervals) {
        int next = x - 1;
        offset = current;
        sort(edges.begin(), edges.end());
        vector<Edge>taken;
        int mst = MST(edges, n, taken);
        vector<int>points;
        while(queryId < k && queries[queryId] <= next) {
            q = queries[queryId];
            points.push_back(q);
            queryId++;
        }
        CalcAtPoints(points, taken, result);
        current = next + 1;
    }
    
    
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
