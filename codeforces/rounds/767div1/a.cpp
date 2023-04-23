#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>a(n);
    vector<vector<int>>pos(n + 1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for(int i = 0; i <= n; i++)
        reverse(pos[i].begin(), pos[i].end());
    set<int>emptyIndices;
    for(int i = 0; i <= n; i++)
        if(pos[i].empty())
            emptyIndices.insert(i);
    vector<int>b;
    int rightmostTaken = -1;
    while(emptyIndices.find(0) == emptyIndices.end()) {
        int x = *emptyIndices.begin();
        int rightmost = -1;
        for(int i = 0; i < x; i++)
            rightmost = max(rightmost, pos[i].back());
        for(int i = 0; i < x; i++) {
            while(!pos[i].empty() && pos[i].back() <= rightmost)
                pos[i].pop_back();
            if(pos[i].empty())
                emptyIndices.insert(i);
        }
        b.push_back(x);
        rightmostTaken = rightmost;
    }
    
    for(int i = 0; i <= n; i++) {
        while(!pos[i].empty() && pos[i].back() <= rightmostTaken)
            pos[i].pop_back();
        while(!pos[i].empty()) {
            pos[i].pop_back();
            b.push_back(0);
        }
    }
    cout << b.size() << '\n';
    for(auto x : b)
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
