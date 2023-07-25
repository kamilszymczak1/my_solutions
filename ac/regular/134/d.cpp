#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;


int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>a(n * 2);
    for(int &x : a)
        cin >> x;
    
    map<int, vector<pair<int, int>>>m;
    
    vector<bool>taken(n, false);
    
    for(int i = 0; i < n; i++)
        m[a[i]].emplace_back(a[i + n], i);
    
    
    
    auto smallest = *min_element(a.begin(), a.begin() + n);
    
    sort(m[smallest].begin(), m[smallest].end());
    
    if(m[smallest][0].first <= smallest) {
        cout << smallest << ' ' << m[smallest][0].first << '\n';
        return 0;
    }
    
    set<pair<int, int>>s;
    auto firstDiff = s.end();
    
    bool first = true;
    int firstFreeIndex = 0;
    for(auto &[value, vec] : m) {
        vector<pair<int, int>>newVec;
        for(auto [value2, index] : vec) {
            if(index >= firstFreeIndex) {
                newVec.emplace_back(value2, index);
            }
        }
        swap(vec, newVec);
        sort(vec.begin(), vec.end());
        
        if(!first && s.begin() -> second < value)
            break;
        
        if(!first && s.begin() -> second == value) {
            if(firstDiff == s.end())
                break;
            
            auto it = firstDiff; it++;
            if(firstDiff -> second > it -> second)
                break;
        }
        
        for(auto [value2, index] : vec) {
            auto it = s.insert(make_pair(index, value2)).first;
            if(it != s.begin()) {
                auto itL = it; itL--;
                if(itL -> second != it -> second && (firstDiff == s.end() || itL -> first < firstDiff -> first)) {
                    firstDiff = itL;
                }
            }
            auto itR = it; itR++;
            if(itR != s.end()) {
                if(it -> second != itR -> second && (firstDiff == s.end() || it -> first < firstDiff -> first)) {
                    firstDiff = it;
                }
            }
            taken[index] = true;
            firstFreeIndex = max(firstFreeIndex, index + 1);
        }
        first = false;
    }
    
    for(int i = 0; i < 2; i++) {
        for(int j = 0; j < n; j++) {
            if(taken[j]) {
                cout << a[i * n + j] << ' ';
            }
        }
    }
    cout << '\n';
    
    return 0;
}
