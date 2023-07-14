#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++)
            cout << n - j << ' ';
        cout << "1 ";
        for(int j = i + 1; j < n; j++)
            cout << n - j + 1 << ' ';
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
