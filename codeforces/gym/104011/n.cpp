#include <iostream>
#include <vector>
#include <set>
#include <assert.h>
#include <queue>
    
using namespace std;
    
const int MAX_N = 300'007;
    
pair<int, int>degrees[MAX_N];
int n;
    
struct white_cmp {
    inline bool operator() (int a, int b) const {
        if(degrees[a].first == degrees[b].first)
            return a < b;
        return degrees[a].first > degrees[b].first;
    }
};
    
struct black_cmp {
    inline bool operator() (int a, int b) const {
        if(degrees[a].second == degrees[b].second)
            return a < b;
        return degrees[a].second > degrees[b].second;
    }
};
    
vector<int>white_leaves, black_leaves;
set<int, white_cmp>white_non_leaves;
set<int, black_cmp>black_non_leaves;
    
void test_case() {
    white_leaves.clear();
    white_non_leaves.clear();
    black_leaves.clear();
    black_non_leaves.clear();
    cin >> n;
    long long white_sum = 0, black_sum = 0;
    for(int i = 0; i < n; i++) {
        cin >> degrees[i].first >> degrees[i].second;
        white_sum += degrees[i].first;
        black_sum += degrees[i].second;
    }
    
    if(white_sum % 2 != 0 || black_sum % 2 != 0 || white_sum + black_sum != 2 * (n - 1)) {
        cout << "No\n";
        return;
    }
    
    if(n == 1) {
        cout << "Yes\n";
        return;
    }
    
    for(int i = 0; i < n; i++) {
        if(degrees[i].first + degrees[i].second == 0) {
            cout << "No\n";
            return;
        }
        
        if(degrees[i].first * 2 > white_sum) {
            cout << "No\n";
            return;
        }
        
        if(degrees[i].second * 2 > black_sum) {
            cout << "No\n";
            return;
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(degrees[i].first + degrees[i].second == 1) {
            if(degrees[i].first == 1) {
                white_leaves.push_back(i); 
            } else {
                black_leaves.push_back(i);
            }
        } else {
            if(degrees[i].first > 0)
                white_non_leaves.insert(i);
            if(degrees[i].second > 0)
                black_non_leaves.insert(i);
        }
    }
    
    vector<pair<pair<int, int>, char>>ans;
    
    for(int i = 2; i < n; i++) {
        
        if(black_leaves.empty()) {
            
            if(white_non_leaves.empty()) {
                cout << "No\n";
                return;
            }
            
            int x = white_leaves.back();
            white_leaves.pop_back();
            int y = *white_non_leaves.begin();
            
            ans.emplace_back(make_pair(x, y), 'W');
            white_non_leaves.erase(white_non_leaves.begin());
            degrees[y].first--;
            if(degrees[y].first + degrees[y].second == 1) {
                black_non_leaves.erase(y);
                if(degrees[y].first == 1)
                    white_leaves.push_back(y);
                if(degrees[y].second == 1)
                    black_leaves.push_back(y);
            } else {
                if(degrees[y].first != 0)
                    white_non_leaves.insert(y);
            }
        } else {
            
            if(black_non_leaves.empty()) {
                cout << "No\n";
                return;
            }
            
            int x = black_leaves.back();
            black_leaves.pop_back();
            
            int y = *black_non_leaves.begin();
            
            ans.emplace_back(make_pair(x, y), 'B');
            black_non_leaves.erase(black_non_leaves.begin());
            degrees[y].second--;
            if(degrees[y].first + degrees[y].second == 1) {
                white_non_leaves.erase(y);
                if(degrees[y].first == 1)
                    white_leaves.push_back(y);
                if(degrees[y].second == 1)
                    black_leaves.push_back(y);
            } else {
                if(degrees[y].second != 0)
                    black_non_leaves.insert(y);
            }
        }
        
    }
    
    if(black_leaves.empty()) {
        assert(white_leaves.size() == 2);
        int x = white_leaves.back(); white_leaves.pop_back();
        int y = white_leaves.back(); white_leaves.pop_back();
        ans.emplace_back(make_pair(x, y), 'W');
    } else {
        assert(black_leaves.size() == 2);
        int x = black_leaves.back(); black_leaves.pop_back();
        int y = black_leaves.back(); black_leaves.pop_back();
        ans.emplace_back(make_pair(x, y), 'B');
    }
    
    cout << "Yes\n";
    for(auto [p, c] : ans) {
        cout << p.first + 1 << ' ' << p.second + 1 << ' ' << c << '\n';
    }
    
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
