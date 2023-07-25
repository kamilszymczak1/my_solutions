#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <bitset>

using namespace std;

void test_case() {
    int n; cin >> n;
    vector<pair<int, int>>a(n);
    
    for(int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i;
    }
    
    sort(a.begin(), a.end());
    
    int a_zero_count = 0;
    while(a_zero_count < n && a[a_zero_count].first == 0)
        a_zero_count++;
    
    if(a_zero_count == n) {
        cout << "YES\n";
        for(int i = 0; i < n; i++)
            cout << "-1\n";
        return;
    }
    
    
    vector<int>answer(n);
    int right_one_count = 0;
    int l = 0;
    int r = n - 1;
    for(int x = n; x > 0; x--) {
        if(a[l].first == right_one_count) {
            answer[a[l].second] = -x;
            l++;
        } else {
            answer[a[r].second] = x;
            r--;
            right_one_count++;
        }
    }
    
    for(auto &[x, y] : a)
        swap(x, y);
    sort(a.begin(), a.end());
    for(auto &[x, y] : a)
        swap(x, y);
    
    vector<int>answer_sorted = answer;
    sort(answer_sorted.begin(), answer_sorted.end());
    
    for(int i = 0; i < n; i++) {
        int count = answer_sorted.end() - upper_bound(answer_sorted.begin(), answer_sorted.end(), -answer[i]);
        if(count != a[i].first) {
            cout << "NO\n";
            return;
        }
    }
    
    cout << "YES\n";
    for(auto x : answer)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
