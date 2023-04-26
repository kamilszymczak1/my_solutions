#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    int size = 31 - __builtin_clz(n);
    if(n == (1 << size))
        size--;
    vector<bool>used(n, false);
    vector<pair<int, int>>p;
    for(int i = n - 1; i >= (1 << size); i--) {
        p.emplace_back(i, i ^ (1 << size));
        used[i] = true;
        used[i ^ (1 << size)] = true;
    }
    
    for(int i = 0; i < (int)p.size() - ((int)p.size() % 2); i++) {
        if(i % 2 == 0) {
            cout << p[i].second << ' ' << p[i].first << ' ';
        } else {
            cout << p[i].first << ' ' << p[i].second << ' ';
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(!used[i]) {
            cout << i << ' ';
        }
    }
    
    if(p.size() % 2 == 1) {
        cout << p.back().second << ' ' << p.back().first;
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
