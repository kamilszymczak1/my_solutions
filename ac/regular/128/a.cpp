#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<int>a(n);
    vector<bool>ans(n, false);
    for(auto  &x : a)
        cin >> x;
    for(int i = 0; i < n; i++) {
        while(i < n - 1 && a[i] <= a[i + 1])
            i++;
        if(i != n - 1) {
            ans[i] = true;
            i++;
            while(i < n - 1 && a[i] > a[i + 1])
                i++;
            ans[i] = true;
        }
    }
    
    for(auto x : ans)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
