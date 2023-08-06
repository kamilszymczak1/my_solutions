#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
void test_case() {
    int n; cin >> n;
    vector<int>a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    sort(a.begin(), a.end());
    vector<int>b = a;
    reverse(b.begin(), b.end());
    int l = n, r = -1;
    for(int i = 0; i < n; i++) {
        if(a[i] == b[i]) {
            l = min(l, i);
            r = max(r, i);
        }
    }
    
    if(n == 1) {
        cout << "NO\n";
        return;
    }
    
    if(l == n && r == -1) {
        cout << "YES\n";
        return;
    }
    
    
    if(a[l] != 1) {
        cout << "YES\n";
        return;
    }
    
    
    long long sum = 0;
    for(int i = r + 1; i < n; i++) {
        if(b[i] != 1) {
            sum += a[i] - 1;
        } else {
            sum += max(0, a[i] - 2);
        }
    }
    
    for(int i = 0; i < r; i++) {
        if(b[i] != 1) {
            sum += a[i] - 1;
        } else {
            sum += max(0, a[i] - 2);
        }
    }
    
    if(sum < r - l + 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
