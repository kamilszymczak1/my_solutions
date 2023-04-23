#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>v(n);
    for(auto &x : v)
        cin >> x;
    bool b[2] = {false, false}, ok = false;
    long long sum[2] = {0, 0}, cnt[2] = {0, 0};
    for(int i = 1; i <  n - 1; i++) {
        b[v[i] % 2] = true;
        sum[v[i] % 2] += v[i];
        cnt[v[i] % 2]++;
        if(v[i] > 1)
            ok = true;
    }
    if(b[1] == false) {
        cout << sum[0] / 2 << '\n';
    } else {
        if(n == 3 || !ok) {
            cout << "-1\n";
            return;
        }
        long long s = sum[0] + sum[1] - cnt[1];
        long long moves = cnt[1] + s / 2;
        cout << moves << '\n';
    }
    
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
