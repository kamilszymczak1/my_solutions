#include <bits/stdc++.h>
using namespace std;
    
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    const int inf = 1 << 30;
    
    vector<string>s(2);
    vector<vector<int>>next_one(2), next_zero(2);
    vector<int>n(2);
    for(int z = 0; z < 2; z++) {
        cin >> s[z];
        n[z] = s[z].size();
        next_one[z].resize(n[z]);
        next_zero[z].resize(n[z]);
        next_one[z].push_back(n[z]);
        next_zero[z].push_back(n[z]);
        next_one[z][n[z] - 1] = next_zero[z][n[z] - 1] = n[z];
        for(int j = n[z] - 2; j >= 0; j--) {
            if(s[z][j + 1] == '1') {
                next_one[z][j] = j + 1;
                next_zero[z][j] = next_zero[z][j + 1];
            } else {
                next_one[z][j] = next_one[z][j + 1];
                next_zero[z][j] = j + 1;
            }
        }
    }
    vector<vector<pair<int, int>>>parent(n[0] + 1, vector<pair<int, int>>(n[1] + 1, make_pair(n[0], n[1])));
    vector<vector<int>>best(n[0] + 1, vector<int>(n[1] + 1, inf));
    vector<vector<char>>color(n[0] + 1, vector<char>(n[1] + 1, '0'));
    
    best[n[0]][n[1]] = 0;
    
    for(int i = n[0]; i >= 0; i--) {
        for(int j = n[1]; j >= 0; j--) {
            
            if(i != n[0] && j != n[1] && s[0][i] != s[1][j])
                continue;
            
            //we choose zero
            int next_i = next_zero[0][i];
            int next_j = next_zero[1][j];
            
            if(best[next_i][next_j] + 1 < best[i][j]) {
                best[i][j] = best[next_i][next_j] + 1;
                parent[i][j] = make_pair(next_i, next_j);
                color[i][j] = '0';
            }
            
            //we choose one
            next_i = next_one[0][i];
            next_j = next_one[1][j];
            
            if(best[next_i][next_j] + 1 < best[i][j]) {
                best[i][j] = best[next_i][next_j] + 1;
                parent[i][j] = make_pair(next_i, next_j);
                color[i][j] = '1';
            }
            
        }
    }
    
    int first_one_1 = s[0][0] == '1' ? 0 : next_one[0][0];
    int first_one_2 = s[1][0] == '1' ? 0 : next_one[1][0];
    
    int first_zero_1 = s[0][0] == '0' ? 0 : next_zero[0][0];
    int first_zero_2 = s[1][0] == '0' ? 0 : next_zero[1][0];
    
    vector<string>answer;
    
    if(first_zero_1 != n[0] || first_zero_2 != n[1]) {
        string t = "";
        pair<int, int>start = make_pair(first_zero_1, first_zero_2);
        if(first_zero_1 == n[0])
            t += s[1][first_zero_2];
        else
            t += s[0][first_zero_1];
            
        while(start != make_pair(n[0], n[1])) {
            t += color[start.first][start.second];
            start = parent[start.first][start.second];
        }
        answer.push_back(t);
    } else {
        answer.push_back("0");
    }
    
    if(first_one_1 != n[0] || first_one_2 != n[1]) {
        string t = "";
        pair<int, int>start = make_pair(first_one_1, first_one_2);
        if(first_one_1 == n[0])
            t += s[1][first_one_2];
        else
            t += s[0][first_one_1];
            
        while(start != make_pair(n[0], n[1])) {
            t += color[start.first][start.second];
            start = parent[start.first][start.second];
        }
        answer.push_back(t);
    } else {
        answer.push_back("1");
    }
    
    if(answer.size() == 1) {
        cout << s[0] << '\n';
    } else {
        if(answer[0].size() == answer[1].size()) {
            cout << min(answer[0], answer[1]) << '\n';
        } else {
            if(answer[0].size() < answer[1].size())
                cout << answer[0] << '\n';
            else
                cout << answer[1] << '\n';
            
        }
    }
        
    
    return 0;
}
