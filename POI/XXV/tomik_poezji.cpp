include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, s; cin >> n >> s;
    vector<vector<int>>ind(s);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ind[(x + 1) % s].push_back(i + 1);
    }
    
    set<pair<int, int>, greater<pair<int, int>>>S;
    
    for(int i = 0; i < s; i++)
        if(!ind[i].empty())
            S.insert(make_pair(ind[i].size(), i));
        
    int current = 0, result = 0;
    vector<int>ans;
    while(S.size() > 1) {
        auto it = S.begin();
        if((current + it -> second) % s == s - 1)
            it++;
        pair<int, int>next = *it;
        S.erase(it);
        ans.push_back(ind[next.second].back());
        ind[next.second].pop_back();
        current = (current + next.second) % s;
        if(next.first != 1)
            S.insert(make_pair(next.first - 1, next.second)); 
        
    }
    
    int lastIndex = S.begin() -> second;
    
    while(ind[lastIndex].size() > 0) {
        if(current == s - 1) {
            result++;
            current = 0;
        }
        current = (current + lastIndex) % s;
        ans.push_back(ind[lastIndex].back());
        ind[lastIndex].pop_back();
    }
    
    cout << result << '\n';
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
