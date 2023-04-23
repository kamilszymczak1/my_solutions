#include <iostream>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int t, n;
    string s, result;
    cin >> t;
    for(int i = 0; i < t; i++) {
        cin >> n >> s;
        result = "";
        for(int i = 0; i < n; i++)
            result = result + s[i * 2];
        cout << result << "\n";
    }
    
    return 0;
}
