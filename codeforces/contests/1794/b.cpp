#include <iostream>
#include <vector>

using namespace std;

void test_case() {
    int n; cin >> n;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    for(int i = 0; i < n - 1; i++) {
        a[i] = max(a[i], 2);
    }
    for(int i = 0; i < n - 1; i++) {
        while(a[i + 1] % a[i] == 0)
            a[i + 1]++;
    }
    for(int &x : a)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
