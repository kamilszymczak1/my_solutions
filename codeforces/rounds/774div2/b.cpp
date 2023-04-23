#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    long long S = 0;
    vector<long long>a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        S += a[i];
    }
    sort(a.begin(), a.end());
    long long prefixSum = a[0], suffixSum = 0;
    for(int i = 1; i < n - i; i++) {
        prefixSum += a[i];
        suffixSum += a[n - i];
        if(prefixSum < suffixSum) {
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
