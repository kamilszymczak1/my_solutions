#include <iostream>
#include <vector>
#include <map>

using namespace std;

void TestCase() {
    int n; cin >> n;
    long long total;
    cout << "? " << 1 << ' ' << n << '\n' << flush;
    cin >> total;
    int beg = 1;
    map<int, long long>m;
    int log2N = 0;
    while((1  << (log2N + 1)) < n)
        log2N++;
    for(int i = log2N; i >= 0; i--) {
        cout << "? " << 1 << ' ' << beg + (1 << i) << '\n' << flush;
        long long x; cin >> x;
        m[beg + (1 << i)] = x;
        if(x == 0)
            beg += (1 << i);
    }
    
    int begRange = beg + 1, endRange = n;
    for(auto [ind, inv] : m) {
        if(ind < beg)
            continue;
        long long len = ind - beg + 1;
        long long maxInv = len * (len - 1) / 2;
        if(maxInv == inv) {
            begRange = ind;
        }
        if(maxInv > inv) {
            endRange = ind;
        }
    }
    
    int rangeLength = endRange - begRange + 1;
    log2N = 0;
    while((1  << (log2N + 1)) < rangeLength)
        log2N++;
    long long leftInv = 0;
    for(int i = log2N; i >= 0; i--) {
        cout << "? " << 1 << ' ' << begRange + (1 << i) << '\n' << flush;
        long long x; cin >> x;
        long long len = begRange + (1 << i) - beg + 1;
        long long maxInv = len * (len - 1) / 2;
        if(maxInv == x) {
            leftInv = x;
            begRange += 1 << i;
        }
    }
    
    long long X = beg, Y = begRange + 1;
    long long P = Y - X;
    long long K = 1;
    for(int i = 29; i >= 0; i--) {
        K += 1 << i;
        long long A = P * (P - 1) / 2 + K * (K - 1) / 2;
        if(A > total)
            K -= 1 << i;
    }
    
    cout << "! " << X << ' ' << Y << ' ' << Y + K - 1 << '\n' << flush;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
