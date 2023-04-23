#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    for(int i = 0; i < n - 1; i++) {
        if(a[i] > a[i + 1]) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
