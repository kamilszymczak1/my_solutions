#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int inf = 1e9 + 7;

const int leafCount = 1 << 20;
int values[leafCount << 1], lazy[leafCount << 1];
void Propagate(int v) {
    values[v] += lazy[v];
    if(v < leafCount) {
        lazy[v * 2] += lazy[v];
        lazy[v * 2 + 1] += lazy[v];
    }
    lazy[v] = 0;
}

void AddRec(int a, int b, int lo, int hi, int v, int value) {
    Propagate(v);
    if(a == lo && b == hi) {
        lazy[v] += value;
        Propagate(v);
        return;
    }
    if(a >= b)
        return;
    int mid = (lo + hi) / 2;
    AddRec(a, min(b, mid), lo, mid, v * 2, value);
    AddRec(max(a, mid), b, mid, hi, v * 2 + 1, value);
    values[v] = min(values[v * 2], values[v * 2 + 1]);
}

void Add(int a, int b, int value) {
    return AddRec(a, b + 1, 0, leafCount, 1, value);
}

int GetMinRec(int a, int b, int lo, int hi, int v) {
    Propagate(v);
    if(a == lo && b == hi)
        return values[v];
    if(a >= b)
        return inf;
    const int mid = (lo + hi) / 2;
    const int L = GetMinRec(a, min(b, mid), lo, mid, v * 2);
    const int R = GetMinRec(max(a, mid), b, mid, hi, v * 2 + 1);
    return min(L, R);
}

int GetMin(int a, int b) {
    return GetMinRec(a, b + 1, 0, leafCount, 1);
}

struct Segment {
    int a, b, w;
    Segment() : a(0), b(0), w(0) {}
    Segment(int _a, int _b, int _w) : a(_a), b(_b), w(_w) {}
};

inline bool operator<(const Segment &a, const Segment &b) {
    return a.w < b.w;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    m--;
    vector<Segment>segment(n);
    for(Segment &s : segment) {
        cin >> s.a >> s.b >> s.w;
        s.b--;
    }
    
    sort(segment.begin(), segment.end());
    
    int end = 0, result = inf;
    for(int beg = 0; beg < n; beg++) {
        while(end < n && (end <= beg || GetMin(1, m) == 0)) {
            Add(segment[end].a, segment[end].b, 1);
            end++;
        }
        if(GetMin(1, m) > 0)
            result = min(result, segment[end - 1].w - segment[beg].w);
        Add(segment[beg].a, segment[beg].b, -1);
    }
    
    cout << result << '\n';
    
    
    return 0;
}

