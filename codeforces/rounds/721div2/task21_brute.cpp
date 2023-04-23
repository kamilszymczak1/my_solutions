#include <iostream>

using namespace std;

string s;

int Wins(int firstSpend, int secondSpend, bool reversed) {
    int cz = 0;
    for(auto x : s)
        if(x == '0')
            cz++;
    if(cz == 0) {
        if(firstSpend < secondSpend)
            return 1;
        if(firstSpend == secondSpend)
            return 0;
        return -1;
    }
    
    bool draw = false;
    
    bool palindrome = true;
    for(int i = 0; i < s.size() / 2; i++)
        if(s[i] != s[s.size() - i - 1])
            palindrome = false;
        
    if(!palindrome && !reversed) {
        int t = Wins(secondSpend, firstSpend, true);
        if(t == -1)
            return 1;
        if(t == 0)
            draw = true;
    }
    
    for(int i = 0; i < s.size(); i++) {
        if(s[i] == '0') {
            s[i] = '1';
            int t = Wins(secondSpend, firstSpend + 1, false);
            if(t == -1)
                return 1;
            if(t == 0)
                draw = true;
            s[i] = '0';
        }
    }
    if(draw)
        return 0;
    return -1;       
}

int main() {
    ios_base::sync_with_stdio(0);
    cin >> s;
    cout << Wins(0, 0, 0) << '\n';
    
    
    return 0;
}
