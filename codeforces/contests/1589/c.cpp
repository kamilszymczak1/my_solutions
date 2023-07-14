#include <iostream>
#include <vector>

using namespace std;

bool TestCase() {
    int n; cin >> n;
    vector<int>cnt1(201, 0), cnt2(201, 0);
    for(int i = 0; i < n; i++) {
        int x; cin >> x; cnt1[x + 100]++;
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x; cnt2[x + 100]++;
    }
    
    int remainingA = 0;
    for(int i = 0; i < 201; i++) {
        if(remainingA > cnt2[i])
            return false;
        cnt2[i] -= remainingA;
        if(cnt1[i] < cnt2[i])
            return false;
        cnt1[i] -= cnt2[i];
        remainingA = cnt1[i];
    }
    return remainingA == 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--) {
        cout << (TestCase() ? "YES" : "NO") << '\n';
    }
    
    return 0;
}
