#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, k; cin >> n >> k;
    vector<int>match(n);
    for(int i = 0; i < n; i++) {
        match[i] = i ^ (n - 1);
    }
    
    if(k == n - 1) {
        if(n == 4) {
            cout << "-1\n";
            return;
        }
        match[n - 1] = n - 4;
        match[n - 4] = n - 1;
        match[n - 2] = 2;
        match[2] = n - 2;
        match[n - 3] = 1;
        match[1] = n - 3;
        match[0] = 3;
        match[3] = 0;
    } else {
        match[n - 1] = k;
        match[k] = n - 1;
        match[0] = k ^ (n - 1);
        match[k ^ (n - 1)] = 0;
    }
    
    
    
    for(int i = 0; i < n; i++) {
        if(i < match[i]) {
            cout << i << ' ' << match[i] << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
