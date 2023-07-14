#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct SegTree {
    struct Node {
        int value;
        bool set;
        Node() : value(0), set(false) {}
    } nodes[1 << 19];
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        Clear();
    }
    void SetZero(int a, int b) {
        return SetZeroRec(a, b + 1, 0, leafCount, 1);
    }
    void SetZeroRec(int a, int b, int lo, int hi, int v) {
        if(nodes[v].set || a >= b)
            return;
        if(a == lo && b == hi) {
            nodes[v].set = true;
            nodes[v].value = 0;
            return;
        }
        int mid = (lo + hi) / 2;
        SetZeroRec(a, min(b, mid), lo, mid, v * 2);
        SetZeroRec(max(a, mid), b, mid, hi, v * 2 + 1);
        nodes[v].value = nodes[v * 2].value + nodes[v * 2 + 1].value;
    }
    int Sum(int a, int b) {
        return SumRec(a, b + 1, 0, leafCount, 1);
    }
    int SumRec(int a, int b, int lo, int hi, int v) {
        if(nodes[v].set || a >= b)
            return 0;
        if(a == lo && b == hi)
            return nodes[v].value;
        int mid = (lo + hi) / 2;
        int L = SumRec(a, min(b, mid), lo, mid, v * 2);
        if(L > 1)
            return L;
        int R = SumRec(max(a, mid), b, mid, hi, v * 2 + 1);
        return L + R;
    }
    int GetNonZeroIndex(int a, int b) {
        return GetNonZeroIndexRec(a, b + 1, 0, leafCount, 1);
    }
    int GetNonZeroIndexRec(int a, int b, int lo, int hi, int v) {
        if(v >= leafCount)
            return v - leafCount;
        int mid = (lo + hi) / 2;
        if(b <= mid) {
            return GetNonZeroIndexRec(a, b, lo, mid, v * 2);
        } else if(a >= mid) {
            return GetNonZeroIndexRec(a, b, mid, hi, v * 2 + 1);
        } else {
            if(SumRec(a, mid, lo, mid, v * 2) == 1) {
                return GetNonZeroIndexRec(a, mid, lo, mid, v * 2);
            } else {
                return GetNonZeroIndexRec(mid, b, mid, hi, v * 2 + 1);
            }
        }
        return 0;
    }
    void Clear() {
        for(int i = leafCount; i < leafCount * 2; i++) {
            nodes[i].set = false;
            nodes[i].value = 1;
        }
        for(int i = leafCount - 1; i; i--) {
            nodes[i].set = false;
            nodes[i].value = nodes[i * 2].value + nodes[i * 2 + 1].value;
        }
    }
};

struct Query {
    int time, l, r;
    Query(int _time, int _l, int _r) {
        time = _time; l = _l; r = _r;
    }
};

void Check(vector<Query>&q0, vector<Query>&q1, vector<int>&minTime, int n, int log, SegTree &T) { 
    int Q0 = q0.size(), Q1 = q1.size();
    vector<pair<int, int>>events;
    for(int i = 0; i < Q1; i++)
        events.emplace_back(minTime[i], i);
    sort(events.begin(), events.end());
    T.Clear();
    int j = 0;
    for(auto [time, id] : events) {
        while(j < (int)q0.size() && q0[j].time < time) {
            T.SetZero(q0[j].l, q0[j].r);
            j++;
        }
        int sum = T.Sum(q1[id].l, q1[id].r);
        if(sum <= 1)
            minTime[id] -= 1 << log;
    }
}

bool cmp(Query &a, Query &b) {
    return a.time < b.time;
}

void TestCase() {
    int n, q; cin >> n >> q;
    vector<Query>q0, q1;
    vector<pair<int, int>>q2;
    SegTree T(n);
    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 0) {
            int l, r, x; cin >> l >> r >> x; l--; r--;
            if(x == 0) {
                q0.emplace_back(i, l, r);
            } else {
                q1.emplace_back(i, l, r);
            }
        } else {
            int j; cin >> j; j--;
            q2.emplace_back(i, j);
        }
    }
    
    int Q0 = q0.size(), Q1 = q1.size();
    vector<int>minTime(Q1, -1);
    for(int log = 17; log >= 0; log--) {
        for(auto &x : minTime)
            x += 1 << log;
        Check(q0, q1, minTime, n, log, T);
    }
    for(int i = 0; i < Q1; i++)
        q1[i].time = max(q1[i].time, minTime[i] + 1);
    sort(q1.begin(), q1.end(), cmp);
    q0.emplace_back(q + 10, 0, 0);
    q1.emplace_back(q + 10, 0, 0);
    T.Clear();
    vector<bool>def(n, false);
    int i = 0, j = 0;
    for(auto [time, index] : q2) {
        while(q0[i].time <= time || q1[j].time <= time) {
            if(q0[i].time <= q1[j].time) {
                T.SetZero(q0[i].l, q0[i].r);
                i++;
            } else {
                int l = q1[j].l, r = q1[j].r;
                def[T.GetNonZeroIndex(l, r)] = true;
                j++;
            }
        }
        if(T.Sum(index, index) == 0) {
            cout << "NO\n";
        } else if(def[index]) {
            cout << "YES\n";
        } else {
            cout << "N/A\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
