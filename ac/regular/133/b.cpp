#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2);
    }
    void Update(int x, int value) {
        for(x += leafCount; x; x /= 2)
            values[x] = max(values[x], value);
    }
    int GetMax(int a, int b) {
        if(b < a)
            return 0;
        a += leafCount; b += leafCount;
        int result = max(values[a], values[b]);
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                result = max(result, values[a + 1]);
            if(b % 2 == 1)
                result = max(result, values[b - 1]);
            a /= 2; b /= 2;
        }
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>P(n), Q(n), positionAtQ(n + 1);
    for(int &x : P)
        cin >> x;
    for(int i = 0; i < n; i++) {
        cin >> Q[i];
        positionAtQ[Q[i]] = i;
    }
    
    SegTree T(n + 7);
    for(int i = 0; i < n; i++) {
        int a = P[i];
        vector<int>newDpValues;
        for(int j = a; j <= n; j += a) {
            int pos = positionAtQ[j];
            int m = T.GetMax(0, pos - 1);
            newDpValues.push_back(m + 1);
        }
        for(int j = a; j <= n; j += a) {
            int pos = positionAtQ[j];
            T.Update(pos, newDpValues[j / a - 1]);
        }
    }
    
    cout << T.GetMax(0, n) << '\n';
    
    return 0;
}
