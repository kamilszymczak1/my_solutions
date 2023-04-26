#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int n) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2, 1 << 30);
    }
    void Set(int x, int value) {
        x += leafCount;
        values[x] = min(values[x], value);
        for(x /= 2; x; x /= 2)
            values[x] = min(values[x * 2], values[x * 2 + 1]);
    }
    int GetMin(int a, int b) { 
        int result = min(values[a += leafCount], values[b += leafCount]);
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                result = min(result, values[a + 1]);
            if(b % 2 == 1)
                result = min(result, values[b - 1]);
            a /= 2; b /= 2;
        }
        return result;
    }
};

int Check(string &s) {
    int n = s.size();
    vector<int>pref(n + 1, 0);
    for(int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + s[i - 1] - '0';
    
    int result = 0;
    SegTree T(n * 3 + 7);
    for(int i = 0; i <= n; i++) {
        result = max(result, pref[i] - T.GetMin(2 * pref[i] - i + 1 + n, n * 3 + 6));
        T.Set(2 * pref[i] - i + n, pref[i]);
    }
    return result;
}

void TestCase() {
    string s; cin >> s;
    int result = Check(s);
    for(char &c : s)
        if(c == '0')
            c = '1';
        else
            c = '0';
        cout << max(result, Check(s)) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
