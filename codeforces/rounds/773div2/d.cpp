#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <deque>

using namespace std;

void TestCase() {
    int n; cin >> n;
    deque<int>q;
    map<int, int>cnt;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        q.push_back(x);
        cnt[x]++;
    }
    
    for(auto [key, value] : cnt) {
        if(value % 2 == 1) {
            cout << "-1\n";
            return;
        }
    }
    
    vector<int>segments;
    int size = 0;
    vector<pair<int, int>>moves;
    while(!q.empty()) {
        int x = q.front(); q.pop_front();
        vector<int>middle;
        while(q.front() != x) {
            middle.push_back(q.front());
            q.pop_front();
        }
        q.pop_front();
        size += middle.size() + 2;
        for(int i = 0; i < (int)middle.size(); i++)
            moves.emplace_back(size++, middle[i]);
        segments.push_back(middle.size() * 2 + 2);
        for(int y : middle)
            q.push_front(y);
    }
    
    cout << moves.size() << '\n';
    for(auto [index, colour] : moves)
        cout << index << ' ' << colour << '\n';
    cout << segments.size() << '\n';
    for(int x : segments)
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
