#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; long long k; cin >> n >> k;
    map<long long, int>cnt;
    cnt[0] = 1;
    long long sum = 0, result = 0;
    for(int i = 0; i < n; i++) {
        long long x; cin >> x;
        sum += x;
        result += cnt[sum - k];
        cnt[sum]++;
    }
    
    cout << result << '\n';
    
    return 0;
}
