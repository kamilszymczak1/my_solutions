#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>p(n);
    int zeroPosition = 0;
    for(int i = 0; i < n; i++) {
        cin >> p[i]; p[i]--;
        if(p[i] == 0)
            zeroPosition = i;
    }
    
    int result = n + 10;
    if(p[(zeroPosition + 1) % n] == 1) {
        //increasing
        result = min(zeroPosition, n - zeroPosition + 2);
    } else {
        //decreasing
        result = min(zeroPosition + 2, n - zeroPosition);
    }
    
    cout << result << '\n';
    
    
    return 0;
}
