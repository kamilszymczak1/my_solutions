#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n, m;
    cin >> t;
    for(int i = 0; i < t; i++) {
        int result = 0;
        cin >> n >> m;
        string s;
        for(int i = 1; i < n; i++) {
            cin >> s;
            result += s[m - 1] == 'R' ? 1 : 0;
        }
        cin >> s;
        for(int i = 0; i < m - 1; i++)
            result += s[i] == 'D' ? 1 : 0;
        
        cout << result << "\n";
    }
    
    return 0;
}

