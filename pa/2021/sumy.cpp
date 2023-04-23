#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool Check(int ind, vector<pair<int, int>>&v) {
    long long M = v[ind].first;
    for(int i = 0; i < (int)v.size(); i++) {
        if(i == ind)
            continue;
        if(v[i].first >= M)
            return false;
        M += v[i].first;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<pair<int, int>>v(n);
    vector<bool>result(n, false);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());
    
    int beg = 0, end = n - 1;
    while(beg <= end) {
        int mid = (beg + end) / 2;
        if(Check(mid, v)) {
            end = mid - 1;
        } else {
            beg = mid + 1;
        }
    }
    
    for(int i = beg; i < n; i++)
        result[v[i].second] = true;
    
    for(int i = 0; i < n; i++)
        cout << (result[i] ? 'T' : 'N');
    cout << '\n';
    
    
    return 0;
}
