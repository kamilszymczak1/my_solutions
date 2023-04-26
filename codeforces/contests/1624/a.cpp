#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    int maxx = 0;
    for(int &x : a) {
        cin >> x;
        maxx = max(maxx, x);
    }
    int result = 0;
    for(int &x : a)
        result = max(result, maxx - x);
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
