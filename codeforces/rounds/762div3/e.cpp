#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<long long>v(n), cnt(n + 1), ans(n + 1, -1);
    for(long long &x : v) {
        cin >> x;
        cnt[x]++;
    }
    long long result = 0;
    multiset<long long, greater<long long>>s;
    for(int i = 0; i <= n; i++) {
        ans[i] = result + cnt[i];
        if(cnt[i] == 0) {
            if(s.empty())
                break;
            result += i - *s.begin();
            s.erase(s.begin());
        } else {
            while(cnt[i] > 1) {
                s.insert(i);
                cnt[i]--;
            }
        }
    }
    for(long long x : ans)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
