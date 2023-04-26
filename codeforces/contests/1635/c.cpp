#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    if(a[n - 2] > a[n - 1]) {
        cout << "-1\n";
        return;
    }
    int j = n - 2;
    while(j > 0 && a[j - 1] <= a[j])
        j--;
    int best = a[j] - a[n - 1];
    if(best <= a[j] || j == 0) {
        cout << j << '\n';
        for(int i = 0; i < j; i++)
            cout << i + 1 << ' ' << j + 1 << ' ' << n << '\n';
    } else {
        cout << "-1\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
