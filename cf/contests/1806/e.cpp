#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>
#include <queue>
#include <set>
#include <map>

using namespace std;

const int MAX_N = 100'007;
const int K = 300;

int n, q;
int p[MAX_N], super_p[MAX_N], depth[MAX_N], layer_id[MAX_N];
vector<int>layer[MAX_N], children[MAX_N];
long long a[MAX_N];
vector<vector<long long>>dp[MAX_N];
bool big_layer[MAX_N];
int next_big_layer[MAX_N];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
    p[0] = -1;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 1; i < n; i++) {
        cin >> p[i]; p[i]--;
        children[p[i]].push_back(i);
    }
    
    for(int i = 0; i < n; i++) {
        for(int j : children[i]) {
            depth[j] = depth[i] + 1;
        }
        layer_id[i] = (int)layer[depth[i]].size();
        layer[depth[i]].push_back(i);
    }
    
    
    
    super_p[0] = -1;
    next_big_layer[0] = -1;
    for(int i = 1; i < n; i++) {
        if(layer[i].size() > K) {
            big_layer[i] = true;
            for(int x : layer[i])
                super_p[x] = x;
        } else {
            for(int x : layer[i]) {
                super_p[x] = super_p[p[x]];
            }
        }
        
        if(big_layer[i]) {
            next_big_layer[i] = i;
        } else {
            next_big_layer[i] = next_big_layer[i - 1];
        }
    }
    
    dp[0] = {{a[0] * a[0]}};
    
    for(int i = 1; i < n; i++) {
        if(big_layer[i])
            continue;
        int sz = layer[i].size();
        dp[i].resize(sz);
        for(int j = 0; j < sz; j++) {
            dp[i][j].resize(j + 1);
            for(int k = 0; k <= j; k++) {
                int x = layer[i][j];
                int y = layer[i][k];
                dp[i][j][k] = a[x] * a[y];
                if(!big_layer[i - 1]) {
                    int x_parent = p[x];
                    int y_parent = p[y];
                    int x_parent_id = layer_id[x_parent];
                    int y_parent_id = layer_id[y_parent];
                    if(x_parent_id < y_parent_id)
                        swap(x_parent_id, y_parent_id);
                    dp[i][j][k] += dp[i - 1][x_parent_id][y_parent_id];
                }
            }
        }
    }
    
    while(q--) {
        int x, y; cin >> x >> y; x--; y--;
        long long answer = 0;
        while(x != -1) {
            if(big_layer[depth[x]]) {
                answer += a[x] * a[y];
                x = p[x];
                y = p[y];
            } else {
                int x_id = layer_id[x];
                int y_id = layer_id[y];
                if(x_id < y_id)
                    swap(x_id, y_id);
                answer += dp[depth[x]][x_id][y_id];
                x = super_p[x];
                y = super_p[y];
            }
        }
        
        cout << answer << '\n';
    }
    
    return 0;
}
