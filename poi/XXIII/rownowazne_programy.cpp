#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
constexpr int MAX_K = 1007;

bool commutative[MAX_K][MAX_K];

vector<int>v[2];
int n, k, m;

vector<int> Transform(vector<int>v) {
    vector<bool>used(v.size(), false);
    vector<int>pos(k + 1, 0), result;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= k; j++) {
            while(pos[j] < n && (used[pos[j]] || (v[pos[j]] != j && commutative[j][v[pos[j]]])))
                pos[j]++;
            
            if(pos[j] < n && v[pos[j]] == j && !used[pos[j]]) {
                result.push_back(j);
                used[pos[j]] = true;
                break;
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> k >> m;
    for(int i = 1; i <= k; i++)
        fill(commutative[i], commutative[i] + k + 1, true);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        commutative[a][b] = false;
        commutative[b][a] = false;
    }
    
    for(int i = 0; i < 2; i++) {
        v[i].resize(n);
        for(int j = 0; j < n; j++) {
            cin >> v[i][j];
        }
        v[i] = Transform(v[i]);
    }
    
    
    cout << (v[0] == v[1] ? "TAK" : "NIE") << '\n';
    
    
    return 0;
}
