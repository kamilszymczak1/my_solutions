#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


constexpr int inf = 999999999;
constexpr int MAX_N = 1000007;

vector<int>positions[MAX_N], L(1, 0), R(1, 0);
int n, k, a[MAX_N], l, r;

int bound[2][MAX_N], val[MAX_N];

void Flip() {
    for(int i = 0; i <= k; i++) {
        for(int &x : positions[i])
            x = n - x - 1;
        reverse(positions[i].begin(), positions[i].end());
    }
    reverse(a, a + n);
}

void CalcBound(int t, vector<int>&v) {
    vector<int>ind(v.size(), 0);
    const int len = v.size();
    positions[0][0] = 0;
    for(int j = 1; j < len; j++) {
        while(ind[j] < positions[v[j]].size() && positions[v[j]][ind[j]] < positions[v[j - 1]][ind[j - 1]]) {
            ind[j]++;
        }
        if(ind[j] == positions[v[j]].size())
            return;
    }
    for(int i = 0; i < n; i++) {
        positions[0][0] = i + 1;
        bool inc = true;
        for(int j = 1; j < len && inc; j++) {
            inc = false;
            while(ind[j] < positions[v[j]].size() && positions[v[j]][ind[j]] < positions[v[j - 1]][ind[j - 1]]) {
                ind[j]++;
                inc = true;
            }
            if(ind[j] == positions[v[j]].size())
                return;
        }
        int lastPosition = positions[v.back()][ind.back()];
        if(t == 0) {
            bound[t][a[i]] = min(bound[t][a[i]], lastPosition);
        } else {
            bound[t][a[i]] = max(bound[t][a[i]], n - lastPosition - 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k;
    fill(bound[0], bound[0] + k + 1, inf);
    fill(bound[1], bound[1] + k + 1, -1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        positions[a[i]].push_back(i);
    }
    positions[0].push_back(-1);
    positions[0].push_back(n);
    cin >> l >> r;
    for(int i = 0; i < l; i++) {
        int x; cin >> x;
        L.push_back(x);
    }
    for(int i = 0; i < r; i++) {
        int x; cin >> x;
        R.push_back(x);
    }
    CalcBound(0, L);
    Flip();
    CalcBound(1, R);
    reverse(a, a + n);
    
    for(int i = 1; i <= k; i++) {
        if(bound[0][i] <= bound[1][i]) {
            val[bound[0][i]]++;
            val[bound[1][i] + 1]--;
        }
    }
    
    int sum = 0;
    vector<int>ans;
    for(int i = 0; i < n; i++) {
        sum += val[i];
        if(sum > 0 && a[i] == L.back()) {
            ans.push_back(i + 1);
        }
    }
    
    cout << ans.size() << '\n';
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
