#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    string s; cin >> s;
    vector<deque<int>>pos(26);
    for(int i = 0; i < n; i++)
        pos[s[i] - 'a'].push_back(i);
    
    int r = n - 1, l = 0;
    vector<int>swapWith(n, -1);
    while(l <= r) {
        for(int j = 0; j < s[l] - 'a'; j++) {
            if(!pos[j].empty()) {
                swapWith[l] = pos[j].back();
                r = pos[j].back() - 1;
                break;
            }
        }
        l++;
        for(int i = 0; i < 26; i++) {
            while(!pos[i].empty() && pos[i].front() < l)
                pos[i].pop_front();
            while(!pos[i].empty() && pos[i].back() > r)
                pos[i].pop_back();
        }
    }
    
    for(int i = 0; i < n; i++)
        if(swapWith[i] != -1)
            swap(s[i], s[swapWith[i]]);
        
    cout << s << '\n';
    
    return 0;
}
