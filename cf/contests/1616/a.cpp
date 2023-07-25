#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


void TestCase() {
    int n; cin >> n;
    vector<int>cnt(101, 0);
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        cnt[abs(a)]++;
    }
    int result = min(1, cnt[0]);
    for(int i = 1; i <= 100; i++)
        result += min(2, cnt[i]);
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
