#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    if(a[0] == 1) {
        cout << n + 1 << ' ';
        for(int i = 1; i <= n; i++)
            cout << i << ' ';
        cout << '\n';
    } else if(a[n - 1] == 0) {
        for(int i = 1; i <= n + 1; i++)
            cout << i << ' ';
        cout << '\n';
    } else {
        for(int i = 0; i < n - 1; i++) {
            if(a[i] == 0 && a[i + 1] == 1) {
                for(int j = 1; j <= i + 1; j++)
                    cout << j << ' ';
                cout << n + 1 << ' ';
                for(int j = i + 2; j <= n; j++)
                    cout << j << ' ';
                cout << '\n';
                return;
            }
        }
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
