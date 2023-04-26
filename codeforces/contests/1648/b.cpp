#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

using namespace std;

bool Is(int a, vector<int>&x) {
    int ind = lower_bound(x.begin(), x.end(), a) - x.begin();
    return ind != x.size() && x[ind] == a;
}

void TestCase() {
    int n, c; cin >> n >> c;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    sort(a.begin(), a.end());
    a.resize(unique(a.begin(), a.end()) - a.begin());
    for(auto &y : a) {
        for(int z = 1; z <= c / y + 1; z++) {
            if(!Is(z, a) && y * z <= c) {
                auto it = lower_bound(a.begin(), a.end(), y * z);
                if(it != a.end() && *it / y == z) {
                    cout << "No\n";
                    return;
                }
            }
        }
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
