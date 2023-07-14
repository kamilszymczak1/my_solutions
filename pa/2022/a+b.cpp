#include <iostream>
#include <vector>

using namespace std;

vector<int>convert(string s) {
    vector<int>ans;
    for(int i = (int)s.size() - 1; i >= 0; i--)
        ans.push_back(s[i] - '0');
    return ans;
}

int main() {
    string x, y; cin >> x >> y;
    vector<int>a = convert(x), b = convert(y);
    
    int rem = 0;
    vector<int>ans;
    for(int i = 0; i < (int)max(a.size(), b.size()) || rem != 0; i++) {
        int current = rem;
        if(i < (int)a.size())
            current += a[i];
        if(i < (int)b.size())
            current += b[i];
        ans.push_back(current % 10);
        rem = current / 10;
    }
    for(int i = (int)ans.size() - 1; i >= 0; i--)
        cout << ans[i];
    cout << '\n';
    return 0;
}
