#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
void test_case() {
    int n; cin >> n;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    int result = 0;
    for(int i = 1; i < n; i++) {
        if(a[i - 1] > a[i]) {
            result = max(result, max(a[i - 1], a[i]));
        }
    }
    cout << result << '\n';
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        test_case();
    
    return 0;
}
