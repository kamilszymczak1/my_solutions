#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<int>x(n), cnt(30);
    long long result = 0;
    for(int i = 0; i < n; i++) {
        cin >> x[i];
        for(int j = 0; j < 30; j++)
            cnt[j] += (x[i] >> j) & 1;
        result += x[i];
    }
    
    for(int i = 0; i < n; i++) {
        long long localResult = 0;
        for(int j = 0; j < 30; j++) {
            if((x[i] >> j) & 1) {
                localResult += (n - cnt[j]) * (1ll << j);
            } else {
                localResult += cnt[j] * (1ll << j);
            }
        }
        result = max(result, localResult);
    }
    cout << result << '\n';
    
    return 0;
}
