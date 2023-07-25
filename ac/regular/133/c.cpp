#include <algorithm>
#include <numeric>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    long long h, w, k; cin >> h >> w >> k;
    vector<long long>A(h), B(w);
    long long aSum = 0, bSum = 0;
    for(int i = 0; i < h; i++) {
        cin >> A[i];
        aSum = (aSum + A[i]) % k;
        A[i] = k - (A[i] - (w * (k - 1) % k) + k) % k;
        if(A[i] == k) A[i] = 0;
    }
    for(int i = 0; i < w; i++) {
        cin >> B[i];
        bSum = (bSum + B[i]) % k;
        B[i] = k - (B[i] - (h * (k - 1) % k) + k) % k;
        if(B[i] == k) B[i] = 0;
    }
    
    if(aSum != bSum) {
        cout << "-1\n";
    } else {
        long long result = h * w * (k - 1);
        long long aSub = accumulate(A.begin(), A.end(), 0ll);
        long long bSub = accumulate(B.begin(), B.end(), 0ll);
        cout << result - max(aSub, bSub) << '\n';
    }
    
    return 0;
}
