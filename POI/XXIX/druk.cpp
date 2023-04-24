#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 1007;
char grid[MAX_N][MAX_N];
int taken[MAX_N][MAX_N], turnID = 1;
int charCnt[26], patternACnt[26], patternBCnt[26];
int n, m;

bool HorizontalMatch(int x, int y, string &pattern) {
    if(y + pattern.size() > m)
        return false;
    for(int i = 0; i < pattern.size(); i++)
        if(grid[x][y + i] != pattern[i] || taken[x][y + i] == turnID)
            return false;
    return true;
}

bool VerticalMatch(int x, int y, string &pattern) {
    if(x + pattern.size() > n)
        return false;
    for(int i = 0; i < pattern.size(); i++)
        if(grid[x + i][y] != pattern[i] || taken[x + i][y] == turnID)
            return false;
    return true;
}


bool CheckPattern(string &pattern) {
    turnID++;
    for(int y = 0; y < m; y++) {
        for(int x = 0; x < n; x++) {
            if(taken[x][y] == turnID)
                continue;
            if(VerticalMatch(x, y, pattern)) {
                for(int i = 0; i < pattern.size(); i++)
                    taken[x + i][y] = turnID;
            } else if(HorizontalMatch(x, y, pattern)) {
                for(int i = 0; i < pattern.size(); i++)
                    taken[x][y + i] = turnID;
            } else {
                return false;
            }
        }
    }
    return true;
    
}

bool Check(int len) {
    string patternA = "", patternB = "";
    fill(patternACnt, patternACnt + 26, 0);
    fill(patternBCnt, patternBCnt + 26, 0);
    for(int i = 0; i < len; i++) {
        patternA += grid[0][i];
        patternB += grid[i][0];
        patternACnt[grid[0][i] - 'a']++;
        patternBCnt[grid[i][0] - 'a']++;
    }
    bool result = false, aGood = true, bGood = true;
    int kA = -1, kB = -1;
    for(int i = 0; i < 26; i++) {
        if(charCnt[i] == 0)
            continue;
        if(patternACnt[i] == 0 || charCnt[i] % patternACnt[i] != 0) {
            aGood = false;
        } else {
            if(kA == -1) {
                kA = charCnt[i] / patternACnt[i];
            } else if(charCnt[i] / patternACnt[i] != kA) {
                aGood = false;
            }
        }
        
        if(patternBCnt[i] == 0 || charCnt[i] % patternBCnt[i] != 0) {
            bGood = false;
        } else {
            if(kB == -1) {
                kB = charCnt[i] / patternBCnt[i];
            } else if(charCnt[i] / patternBCnt[i] != kB) {
                bGood = false;
            }
        }

    }
    
    if(aGood)
        result |= CheckPattern(patternA);
    if(bGood)
        result |= CheckPattern(patternB);
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
            charCnt[grid[i][j] - 'a']++;
        }
    }
    
    vector<int>ans;
    if(*max_element(charCnt, charCnt + 26) == n * m) {
        for(int i = 1; i <= max(n, m); i++) {
            if(n % i == 0 || m % i == 0) {
                ans.push_back(i);
            }
        }
    } else {
        for(int i = 2; i <= max(n, m); i++) {
            if((n * m) % i == 0 && Check(i)) {
                ans.push_back(i);
            }
        }
    }
    
    cout << ans.size() << '\n';
    for(int x : ans)
        cout << x << ' ';
    cout << '\n';
    
    return 0;
}
