#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int Skim(int l, int r, vector<int>&a, vector<vector<int>>&pos, int &result) {
    result += r - l - 1;
    int newR = r;
    for(int i = l + 1; i < r; i++) {
        newR = max(newR, pos[a[i]].back());
    }
    int leftmost = r;
    if(newR > r)
        leftmost = Skim(r, newR, a, pos, result);
    return leftmost;
}

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    vector<vector<int>>pos(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i]; a[i]--;
        pos[a[i]].push_back(i);
    }
    int result = 0, i = 0;
    while(i < n) {
        int x = a[i];
        int index = lower_bound(pos[x].begin(), pos[x].end(), i) - pos[x].begin();
        if(index != (int)pos[x].size() - 1) {
            i = Skim(pos[x][index], pos[x].back(), a, pos, result);
        }
        i++;
    }
    
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    
    return 0;
}
