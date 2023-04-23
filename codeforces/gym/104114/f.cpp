#include <iostream>
#include <vector>
    
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<vector<int>>p(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> p[i][j];
        }
    }
    int answer = 0;
    vector<bool>chosen(n, false);
    chosen[n - 1] = true;
    vector<pair<int, int>>matches;
    for(int q = 0; q < n - 1; q++) {
        int last = n - q - 1;
        int best = -1, best_ind = 0;
        for(int j = 0; j < n; j++) {
            if(chosen[j] || j == last)
                continue;
            if(p[last][j] > best) {
                best = p[last][j];
                best_ind = j;
            }
        }
        answer += best;
        vector<int>new_row(n), new_col(n);
        for(int j = 0; j < n; j++)
            new_row[j] = max(p[best_ind][j], p[last][j]);
        for(int j = 0; j < n; j++)
            new_col[j] = max(p[j][best_ind], p[j][last]);
        for(int j = 0; j < n; j++) {
            p[j][best_ind] = new_col[j];
            p[best_ind][j] = new_row[j];
        }
        if(best_ind < last) {
            chosen[last] = true;
        } else {
            chosen[best_ind] = true;
        }
        matches.emplace_back(best_ind, last);
        last = best_ind;
    }
    cout << answer << '\n';
    for(auto [a, b] : matches)
        cout << a + 1 << ' ' << b + 1 << '\n';
    return 0;
}
