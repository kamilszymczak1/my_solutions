#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool Impossible(string s, string &t) {
    sort(s.begin(), s.end());
    return s >= t;
}

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int size, int f) {
        for(leafCount = 1; leafCount < size; leafCount *= 2) {}
        values.resize(leafCount * 2, f);
    }
    int Prefix(int x) {
        int result = values[x + leafCount];
        for(x += leafCount; x; x /= 2)
            if(x % 2 == 1)
                result += values[x - 1];
            return result;
    }
    void Set(int x, int value) {
        for(x += leafCount; x; x /= 2)
            values[x] += value;
    }
};

void TestCase() {
    int n; cin >> n;
    string s, t; cin >> s >> t;
    if(Impossible(s, t)) {
        cout << "-1\n";
        return;
    }
    vector<set<int>>pos(26);
    for(int i = 0; i < n; i++)
        pos[s[i] - 'a'].insert(i);
    long long moves = 0, result = 1ll << 60;
    SegTree T(n, 0);
    for(int com = 0; com < n; com++) {
        for(int c = 0; c < t[com] - 'a'; c++) {
            if(!pos[c].empty()) {
                int nearest = *pos[c].begin();
                long long toMove = nearest + T.Prefix(nearest);
                result = min(result, toMove + moves);
            }
        }
        int tid = t[com] - 'a';
        if(pos[t[com] - 'a'].empty())
            break;
        moves += *pos[tid].begin() + T.Prefix(*pos[tid].begin());
        T.Set(*pos[tid].begin(), -1);
        pos[tid].erase(pos[tid].begin());
    }
    if(result == (1ll << 60)) {
        cout << "-1\n";
    } else {
        cout << result << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
