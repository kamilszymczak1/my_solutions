#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <set>
    
using namespace std;
    
const long long inf = 1ll << 60;
    
bool check(long long r_0, vector<long long>&x, vector<long long>&r) {
    multiset<long long>R;
    for(long long t : r)
        R.insert(t);
    int n = x.size();
    vector<long long>ans(n);
    for(int i = 0; i < n; i++) {
        if(R.find(r_0) == R.end())
            return false;
        R.erase(R.find(r_0));
        ans[i] = r_0;
        r_0 = x[i + 1] - x[i] - r_0;
    }
    for(int i = 0; i < n; i++)
        cout << ans[i] << ' ';
    cout << '\n';
    return true;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<long long>x(n);
    for(int i = 0; i < n; i++)
        cin >> x[i];
    vector<long long>r(n);
    for(int i = 0; i < n; i++) {
        cin >> r[i];
    }
    sort(r.begin(), r.end());
    
    if(n == 1 || n == 2) {
        cout << r[0] << ' ' << r[1] << '\n';
        return 0;
    }
    
    long long min_1 = 0;
    long long min_2 = inf;
    long long l = 0;
    for(int i = 1; i < n; i++) {
        long long dx = x[i] - x[i - 1];
        if(i % 2 == 1) {
            min_2 = min(min_2, dx - l);
            l = dx - l;
        } else {
            min_1 = min(min_1, dx - l);
            l = dx - l;
        }
    }
    
    long long r_0 = r[0] - min_1;
    
    if(check(r_0, x, r)) {
        return 0;
    }
    r_0 = min_2 - r[0];
    if(check(r_0, x, r)) {
        return 0;
    }
    
    return 0;
}
