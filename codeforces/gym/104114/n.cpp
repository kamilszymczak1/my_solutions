#include <iostream>
#include <vector>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    long long m; cin >> m;
    vector<long long>a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    for(int i = 1; i < n; i++) {
        if(a[i - 1] - a[i] > m) {
            a[i] = a[i - 1] - m;
        }
    }
    
    for(int i = n - 2; i >= 0; i--) {
        if(a[i + 1] - a[i] > m) {
            a[i] = a[i + 1] - m;
        }
    }
    
    for(int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << '\n';
    return 0;
}
