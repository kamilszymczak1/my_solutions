#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>v;
    int maxDiff1 = 0, maxDiff2 = 0;
    int bestIndex1 = 0, bestIndex2 = 0;
    int minDiff1 = 1 << 30;
    for(int i = 2; i < n; i++) {
        cout << "? " << 1 << ' ' << i << ' ' << n << '\n' << flush;
        int m; cin >> m;
        if(m >= maxDiff1) {
            maxDiff2 = maxDiff1;
            maxDiff1 = m;
            bestIndex2 = bestIndex1;
            bestIndex1 = i;
        } else if(m >= maxDiff2) {
            maxDiff2 = m;
            bestIndex2 = i;
        }
        minDiff1 = min(minDiff1, m);
    }
    
    
    int bestIndex = 0, maxDiff = 0, minDiff2 = 1 << 30;
    for(int i = 1; i <= n; i++) {
        if(i == bestIndex1 || i == bestIndex2)
            continue;
        cout << "? " << bestIndex1 << ' ' << bestIndex2 << ' ' << i << '\n' << flush;
        int m; cin >> m;
        if(m >= maxDiff) {
            bestIndex = i;
            maxDiff = m;
        }
        minDiff2 = min(minDiff2, m);
    }
    
    if(maxDiff1 == minDiff1 && minDiff2 < maxDiff1) {
        cout << "? " << bestIndex1 << ' ' << bestIndex2 << ' ' << 1 << '\n';
        int m1; cin >> m1;
        cout << "? " << bestIndex1 << ' ' << bestIndex2 << ' ' << n << '\n';
        int m2; cin >> m2;
        if(max(m1, m2) != maxDiff1) {
            cout << "! " << 1 << ' ' << n << '\n' << flush;
            return;
        }        
    }
    
    if(maxDiff == minDiff2) {
        cout << "! " << bestIndex1 << ' ' << bestIndex2  << '\n' << flush;
        return;
    } else {
        cout << "! " << bestIndex1 << ' ' << bestIndex << '\n' << flush;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
