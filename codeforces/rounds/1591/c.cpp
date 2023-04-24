#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long Calc(vector<int>&a, int k) {
    if(a.empty())
        return 0;
    long long result = 0;
    for(int i = (int)a.size() - 1; i >= 0; i -= k)
        result += (long long)a[i] * 2;
    return result - a.back();
}

void TestCase() {
    int n, k; cin >> n >> k;
    vector<int>x1, x2;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x > 0)
            x1.push_back(x);
        else
            x2.push_back(-x);
    }
    sort(x1.begin(), x1.end());
    sort(x2.begin(), x2.end());
    long long result = Calc(x1, k) + Calc(x2, k);
    long long t = 0;
    if(!x1.empty() && !x2.empty()) {
        t = min(x1.back(), x2.back());
    }
    cout << result + t << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
