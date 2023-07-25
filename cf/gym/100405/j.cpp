#include <iostream>
#include <map>
    
using namespace std;
    
const int MAX_N = 5000;
    
string s;
int balls = 0, pos = 0, head = 0;
    
int l[MAX_N], r[MAX_N], subtree[MAX_N];
    
map<int, int>dp[MAX_N];
    
int generate(int current) {
    if(pos >= s.size())
        return -1;
    
    if(s[pos + 1] == ')') {
        l[current] = r[current] = -1;
        pos += 2;
        subtree[current] = 0;
    } else if(s[pos + 1] == 'B') {
        l[current] = r[current] = -1;
        pos += 3;
        subtree[current] = 1;
    } else {
        pos++;
        l[current] = generate(++head);
        r[current] = generate(++head);
        pos++;
        subtree[current] = subtree[l[current]] + subtree[r[current]];
    }
    
    return current;
}
    
int get(int x, int k) {
    if(dp[x].find(k) != dp[x].end())
        return dp[x][k];
    
    if(l[x] == -1) {
        if(k > 1)
            return dp[x][k] = -1;
        return dp[x][k] = subtree[x] == k ? 0 : 1;
    }
    
    if(k % 2 == 0) {
        int L = get(l[x], k / 2);
        int R = get(r[x], k / 2);
        if(L != -1 && R != -1)
            return dp[x][k] = L + R;
        return dp[x][k] = -1;
    }
    
    dp[x][k] = -1;
    
    int L1 = get(l[x], k / 2 + 0);
    int R1 = get(r[x], k / 2 + 1);
    
    if(L1 != -1 && R1 != -1)
        dp[x][k] = L1 + R1;
    
    int L2 = get(l[x], k / 2 + 1);
    int R2 = get(r[x], k / 2 + 0);
    
    if(L2 != -1 && R2 != -1) {
        if(dp[x][k] == -1) {
            dp[x][k] = L2 + R2;
        } else {
            dp[x][k] = min(dp[x][k], L2 + R2);
        }
    }
    
    return dp[x][k];
}
    
int main() {
    ios_base::sync_with_stdio(0);
    while(cin >> s) {
        balls = pos = head = 0;
        generate(0);
        
        for(int i = 0; i <= head; i++)
            dp[i].clear();
        
        int answer = get(0, subtree[0]);
        
        if(answer == -1)
            cout << "impossible\n";
        else
            cout << answer / 2 << '\n';
    }
    
    return 0;
}
