#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int GCD(int x, int y) {
    if(x == 0)
        return y;
    return GCD(y % x, x);
}

struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int n, vector<int>&v) {
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2, 0);
        for(int i = 0; i < n; i++)
            values[i + leafCount] = v[i];
        for(int i = leafCount - 1; i; i--)
            values[i] = __gcd(values[i * 2], values[i * 2 + 1]);
    }
    int GCD(int a, int b) {
        int result = __gcd(values[a += leafCount], values[b += leafCount]);
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                result = __gcd(result, values[a + 1]);
            if(b % 2 == 1)
                result = __gcd(result, values[b - 1]);
            a /= 2; b /= 2;
        }
        return result;
    }
};

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    SegTree T(n, a);
    vector<pair<int, int>>intervals;
    for(int i = 0; i < n; i++) {
        int next = i;
        for(int j = 20; j >= 0; j--) {
            if((next + (1 << j)) >= n)
                continue;
            next += (1 << j);
            int gcd = T.GCD(i, next);
            if(gcd < next - i + 1)
                next -= (1 << j);
        }
        if(T.GCD(i, next) == next - i + 1) {
            intervals.emplace_back(next, i);
        }
    }
    sort(intervals.begin(), intervals.end());
    vector<int>placed(1, -1);
    for(auto [b, a] : intervals) {
        if(placed.back() < a) {
            placed.push_back(b);
        }
    }
    vector<int>ans(n);
    for(int x : placed) {
        if(x != -1)
            ans[x]++;
    }
    for(int i = 1; i < n; i++)
        ans[i] += ans[i - 1];
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    //int t; cin >> t;
    int t = 1;
    while(t--)
        TestCase();
    
    return 0;
}
