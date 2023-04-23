#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    int result = 0;
    for(int i = 0; i < n; i++) {
        int weight = a[i] == 0 ? 2 : 1;
        int l = i + 1;
        int r = n - i;
        result += weight * l * r;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
