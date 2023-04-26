#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 7000;
char text[MAX_N], pattern[MAX_N];

void test_case() {
    int n, m; scanf("%d%d", &n, &m);
    scanf("%s", text);
    scanf("%s", pattern);
    for(int i = n; i >= 0; i--)
        swap(text[i], text[i + 1]);
    for(int i = m; i >= 0; i--)
        swap(pattern[i], pattern[i + 1]);
    text[0] = pattern[0] = 0;
    vector<vector<int>>prev(n + 2, vector<int>(26, -1)), next(n + 2, vector<int>(26, -1));
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 26; j++) {
            if(text[i] == j + 'a') {
                prev[i][j] = i;
            } else {
                prev[i][j] = prev[i - 1][j];
            }
        }
    }
    
    for(int i = n; i > 0; i--) {
        for(int j = 0; j < 26; j++) {
            if(text[i] == j + 'a') {
                next[i][j] = i;
            } else {
                next[i][j] = next[i + 1][j];
            }
        }
    }
    vector<vector<int>>min_time1(n + 2, vector<int>(m + 2, -1)), min_time2(n + 2, vector<int>(m + 2, -1));
    for(int i = 0; i <= n + 1; i++) {
        min_time1[i][0] = 2 * i;
        min_time2[i][m + 1] = n + 1 - i;
    }
    
    for(int text_pref = 1; text_pref <= n; text_pref++) {
        for(int pattern_pref = 1; pattern_pref <= m; pattern_pref++) {
            
            int last = prev[text_pref][pattern[pattern_pref] - 'a'];
            if(last == -1 || min_time1[last - 1][pattern_pref - 1] == -1)
                continue;
            if(last == text_pref) {
                min_time1[text_pref][pattern_pref] = min_time1[text_pref - 1][pattern_pref - 1];
            } else {
                int removed = text_pref - pattern_pref;
                int not_removed = pattern_pref;
                min_time1[text_pref][pattern_pref] = 2 * removed + not_removed;
            }
        }
    }
    
    
    for(int text_suff = n; text_suff > 0; text_suff--) {
        for(int pattern_suff = m; pattern_suff > 0; pattern_suff--) {
            int following = next[text_suff][pattern[pattern_suff] - 'a'];
            
            if(following == -1 || min_time2[following + 1][pattern_suff + 1] == -1)
                continue;
            
            if(following == text_suff) {
                min_time2[text_suff][pattern_suff] = min_time2[text_suff + 1][pattern_suff + 1];
            } else {
                min_time2[text_suff][pattern_suff] = n - text_suff + 1;
            }
            
        }
    }
    
    int result = 1 << 30;
    
    if(min_time2[1][1] != -1)
        result = min(result, min_time2[1][1]);
    
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(min_time1[i][j] != -1 && min_time2[i + 1][j + 1] != -1) {
                result = min(result, min_time1[i][j] + min_time2[i + 1][j + 1] + 1);
            }
        }
    }
    if(result == (1 << 30))
        result = -1;
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        test_case();
    return 0;
}
