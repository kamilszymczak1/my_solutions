#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long Smoothen(vector<int>&x, int z) {
    int n = x.size();
    long long result = 0;
    for(int i = 0; i < n - 1; i++) {
        if(x[i + 1] - x[i] > z) {
            result += x[i + 1] - x[i] - z;
            x[i + 1] = x[i] + z;
        }
    }
    for(int i = n - 2; i >= 0; i--) {
        if(x[i] - x[i + 1] > z) {
            result += x[i] - x[i + 1] - z;
            x[i] = x[i + 1] + z;
        }
    }
    return result;
}
int Check(long long z, vector<int>x, long long m) {
    m -= Smoothen(x, z);
    int n = x.size();
    int L = 0, R = 0;
    long long sum = x[0];
    for(int i = 0; i < n; i++) {
        while(L < i && x[L] - abs(L - i) * z <= 0)
            sum -= x[L++];
        while(R < n - 1 && x[R + 1] - abs(R + 1 - i) * z > 0)
            sum += x[++R];
        if(sum - z * ((i - L) * (i - L + 1ll) + (R - i) * (R - i + 1ll)) / 2 <= m)
            return i + 1;
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    long long m; cin >> m;
    vector<int>x(n);
    for(int &y : x)
        cin >> y;
    int beg = 0, end = 1e9 + 7, resIndex;
    
    while(beg <= end) {
        int mid = (beg + end) / 2;
        int index = Check(mid, x, m);
        if(index != 0) {
            resIndex = index;
            end = mid - 1;
        } else {
            beg = mid + 1;
        }
    }
    cout << resIndex << ' ' << end + 1 << '\n';
    
    return 0;
}
