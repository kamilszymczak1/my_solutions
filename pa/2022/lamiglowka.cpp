#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const long long mod = 1'000'000'007;

vector<vector<int>> shift_up(vector<vector<int>>&v) {
    int n = v.size(), m = v[0].size();
    vector<vector<int>>answer(n, vector<int>(m, -1));
    for(int j = 0; j < m; j++) {
        stack<int>s;
        for(int i = 0; i < n; i++) {
            if(v[i][j] > -1) {
                s.push(v[i][j]);
            }
        }
        while(!s.empty()) {
            answer[(int)s.size() - 1][j] = s.top();
            s.pop();
        }
    }
    return answer;
}

vector<vector<int>> shift_down(vector<vector<int>>&v) {
    int n = v.size(), m = v[0].size();
    vector<vector<int>>answer(n, vector<int>(m, -1));
    for(int j = 0; j < m; j++) {
        stack<int>s;
        for(int i = n - 1; i >= 0; i--) {
            if(v[i][j] > -1) {
                s.push(v[i][j]);
            }
        }
        while(!s.empty()) {
            answer[n - (int)s.size()][j] = s.top();
            s.pop();
        }
    }
    return answer;
}

vector<vector<int>> shift_left(vector<vector<int>>&v) {
    int n = v.size(), m = v[0].size();
    vector<vector<int>>answer(n, vector<int>(m, -1));
    for(int i = 0; i < n; i++) {
        stack<int>s;
        for(int j = 0; j < m; j++) {
            if(v[i][j] > -1) {
                s.push(v[i][j]);
            }
        }
        while(!s.empty()) {
            answer[i][(int)s.size() - 1] = s.top();
            s.pop();
        }
    }
    return answer;
}

vector<vector<int>> shift_right(vector<vector<int>>&v) {
    int n = v.size(), m = v[0].size();
    vector<vector<int>>answer(n, vector<int>(m, -1));
    for(int i = 0; i < n; i++) {
        stack<int>s;
        for(int j = m - 1; j >= 0; j--) {
            if(v[i][j] > -1) {
                s.push(v[i][j]);
            }
        }
        while(!s.empty()) {
            answer[i][m - (int)s.size()] = s.top();
            s.pop();
        }
    }
    return answer;
}

void print(vector<vector<int>>&grid) {
    map<int, char>char_by_id = {{-1, '.'}, {1, 'B'}, {2, 'C'}};
    for(vector<int>row : grid) {
        for(int x : row) {
            cout << char_by_id[x];
        }
        cout << '\n';
    }
}


void apply(vector<vector<int>>&grid, char c) {
    switch(c) {
        case 'L':
            grid = shift_left(grid); break;
        case 'P':
            grid = shift_right(grid); break;
        case 'G':
            grid = shift_up(grid); break;
        case 'D':
            grid = shift_down(grid); break;
    }
}

void apply(vector<vector<int>>&grid, string s) {
    for(char c : s)
        apply(grid, c);
}


vector<vector<int>>combine(vector<vector<int>>a, vector<vector<int>>b) {
    int n = a.size(), m = a[0].size();
    vector<vector<int>>answer(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int x = b[i][j] / m, y = b[i][j] % m;
            answer[i][j] = a[x][y];
        }
    }
    return answer;
}

vector<vector<int>>raise(vector<vector<int>>&v, int k) {
    if(k == 1)
        return v;
    vector<vector<int>>answer = raise(v, k / 2);
    answer = combine(answer, answer);
    if(k % 2 == 1)
        answer = combine(answer, v);
    return answer;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, m; cin >> n >> m;
    
    vector<vector<int>>grid(n, vector<int>(m));
    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int j = 0; j < m; j++) {
            switch(s[j]) {
                case '.': grid[i][j] = -1; break;
                case 'B': grid[i][j] = 1; break;
                case 'C': grid[i][j] = 2; break;
            }
        }
    }
    
    map<char, int>orientation = {{'L', 0}, {'P', 0}, {'G', 1}, {'D', 1}};
    
    int k, i; cin >> k;
    string s; cin >> s;
    vector<char>last(2, -1);
    vector<int>cnt(2, 0);
    for(i = 0; i < k - 1; i++) {
        if(orientation[s[i]] != orientation[s[i + 1]]) {
            apply(grid, s[i]);
            apply(grid, s[i + 1]);
            last[orientation[s[i]]] = s[i];
            last[orientation[s[i + 1]]] = s[i + 1];
            cnt[0] = cnt[1] = 1;
            break;
        }
    }
    
    if(i == k - 1) {
        apply(grid, s[k - 1]);
        print(grid);
        return 0;
    }
    vector<char>cyclic;
    for(i += 2; i < k; i++) {
        while(i < k - 1 && orientation[s[i + 1]] == orientation[s[i]])
            i++;
        if(last[orientation[s[i]]] == s[i]) {
            continue;
        }
        last[orientation[s[i]]] = s[i];
        if(!cyclic.empty() && orientation[cyclic.back()] == orientation[s[i]]) {
            cyclic.pop_back();
            if(cnt[orientation[s[i]]] == 1) {
                cyclic.push_back(s[i]);
            } else {
                cnt[orientation[s[i]]]--;
            }
        } else {
            cnt[orientation[s[i]]]++;
            cyclic.push_back(s[i]);
        }
    }
    
    if(cyclic.size() >= 4) {
        string pattern = "";
        for(int i = 0; i < 4; i++)
            pattern += string(1, cyclic[i]);
        vector<vector<int>>new_grid(n, vector<int>(m));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(grid[i][j] > 0) {
                    new_grid[i][j] = i * m + j;
                } else {
                    new_grid[i][j] = -1;
                }
            }
        }
        apply(new_grid, pattern);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(new_grid[i][j] == -1) {
                    new_grid[i][j] = i * m + j;
                }
            }
        }
        
        new_grid = raise(new_grid, cyclic.size() / 4);
        
        vector<vector<int>>my_grid(n, vector<int>(m));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int x = new_grid[i][j] / m, y = new_grid[i][j] % m;
                my_grid[i][j] = grid[x][y];
            }
        }
        grid = my_grid;
    }
    
    for(int i = (int)cyclic.size() - cyclic.size() % 4; i < cyclic.size(); i++)
        apply(grid, cyclic[i]);
    
    print(grid);
    

    return 0;
}
