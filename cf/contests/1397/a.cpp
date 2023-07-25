#include <iostream>
#include <vector>

using namespace std;

const int R = 26;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n;
    string s;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n;
        vector<int>count(26, 0);
        for(int j = 0; j < n; j++) {
            cin >> s;
            for(int k = 0; k < (int)s.size(); k++)
                count[s[k] - 'a']++;
        }
        bool result = true;
        for(int j = 0; j < 26; j++)
            if(count[j] % n != 0)
                result = false;
            if(result)
                cout << "YES\n";
            else
                cout << "NO\n";
    }
    
    return 0;
}
