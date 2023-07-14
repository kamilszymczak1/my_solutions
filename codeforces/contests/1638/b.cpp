#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a, b;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x % 2)
            a.push_back(x);
        else
            b.push_back(x);
    }
    for(int i = 0; i < (int)a.size() - 1; i++) {
        if(a[i] > a[i + 1]) {
            cout << "NO\n";
            return;
        }
    }
    for(int i = 0; i < (int)b.size() - 1; i++) {
        if(b[i] > b[i + 1]) {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
