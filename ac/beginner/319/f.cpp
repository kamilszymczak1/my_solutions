#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 500;
vector<int>children[MAX_N], medicine_nodes;
int s[MAX_N], g[MAX_N], medicine_id[MAX_N];
int dp[1 << 10], parent_mask[MAX_N];
set<pair<int, int>>enemies[1 << 10];
set<int>medicines[1 << 10];

void dfs(int x) {
    if(s[x] == 0 && x != 0)
        parent_mask[x] |= (1 << medicine_id[x]);
    for(int y : children[x]) {
        parent_mask[y] |= parent_mask[x];
        dfs(y);
    }
}

bool valid_mask(int mask) {
    int new_mask = 0;
    for(int i = 0; i < (int)medicine_nodes.size(); i++) {
        if((mask >> i) & 1) {
            new_mask |= parent_mask[medicine_nodes[i]];
        }
    }
    return new_mask == mask;
}

int push_forward(int strength, set<pair<int, int>>&my_enemies, set<int>&my_medicines) {
    while(!my_enemies.empty() && my_enemies.begin() -> first <= strength) {
        int enemy = my_enemies.begin() -> second;
        strength += g[enemy];
        strength = min(1'000'000'000, strength);
        my_enemies.erase(my_enemies.begin());
        for(int x : children[enemy]) {
            if(s[x] == 0) {
                my_medicines.insert(x);
            } else {
                my_enemies.insert(make_pair(s[x], x));
            }
        }
    }
    return strength;
} 

int main() {
    ios_base::sync_with_stdio(0);
    
    
    int n; cin >> n;
    
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        children[p - 1].push_back(i);
        cin >> p >> s[i] >> g[i];
        if(s[i] == 0) {
            medicine_id[i] = (int)medicine_nodes.size();
            medicine_nodes.push_back(i);
        }
    }
    
    dfs(0);
    
    for(int i = 0; i < (1 << (int)medicine_nodes.size()); i++) {
        dp[i] = -1;
    }
    
    for(int x : children[0]) {
        if(s[x] == 0) {
            medicines[0].insert(x);
        } else {
            enemies[0].insert(make_pair(s[x], x));
        }
    }
    dp[0] = push_forward(1, enemies[0], medicines[0]);
    
    for(int mask = 0; mask < (1 << (int)medicine_nodes.size()); mask++) {
        if(!valid_mask(mask) || dp[mask] == -1)
            continue;
        
        for(int medicine : medicines[mask]) {
            set<pair<int, int>>my_enemies = enemies[mask];
            set<int>my_medicines = medicines[mask];
            my_medicines.erase(medicine);
            for(int x : children[medicine]) {
                if(s[x] == 0) {
                    my_medicines.insert(x);
                } else {
                    my_enemies.insert(make_pair(s[x], x));
                }
            }
            
            int new_strength = push_forward(min(1'000'000'000ll, 1ll * dp[mask] * g[medicine]), my_enemies, my_medicines);
            
            if(new_strength > dp[mask | (1 << medicine_id[medicine])]) {
                dp[mask | (1 << medicine_id[medicine])] = new_strength;
                medicines[mask | (1 << medicine_id[medicine])] = my_medicines;
                enemies[mask | (1 << medicine_id[medicine])] = my_enemies;
            }
        }
    }
    
    if(dp[(1 << medicine_nodes.size()) - 1] != -1 && enemies[(1 << medicine_nodes.size()) - 1].empty()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
    
    return 0;
}
