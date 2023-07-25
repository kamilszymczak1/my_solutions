#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long ceil(long x, long long y) {
    if(x % y == 0)
        return x / y;
    return x / y + 1;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    long long W, L; cin >> L >> W;
    vector<long long>a(n);
    for(long long &x : a)
        cin >> x;
    long long result = ceil(a[0], W);
    for(int i = 1; i < n; i++) {
        long long len = a[i] - a[i - 1] - W;
        result += ceil(max(0ll, len), W);
    }
    result += ceil(max(0ll, L - a[n - 1] - W), W);
    cout << result << '\n';
    
    return 0;
}
