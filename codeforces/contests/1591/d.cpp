#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2);
    }
    void Add(int x, int value) {
        for(x += leafCount; x; x /= 2)
            values[x] += value;
    }
    int Prefix(int x) {
        x += leafCount;
        int result = values[x];
        for(; x > 1; x /= 2)
            result += values[x - 1] * (x % 2);
        return result;
    }
};

void TestCase() {
    int n; cin >> n;
    vector<int>a(n), cnt(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; a[i]--;
        cnt[a[i]]++;
    }
    
    for(int i = 0; i < n; i++) {
        if(cnt[i] == 0) {
            cout << "YES\n";
            return;
        }
    }
    SegTree T(n);
    long long inv = 0;
    for(int i = 0; i < n; i++) {
        int A = n - a[i] - 1;
        if(A > 0)
            inv += T.Prefix(A - 1);
        T.Add(A, 1);
    }
    if(inv % 2 == 0) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
