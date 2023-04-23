#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>a(n);
    for(auto &x : a)
        cin >> x;
    int i = 0;
    while(i < n - 1 && a[i + 1] > a[i])
        i++;
    cout << a[i] << '\n';
    
    return 0;
}
