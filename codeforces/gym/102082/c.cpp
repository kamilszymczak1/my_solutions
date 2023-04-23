#include <iostream>
#include <vector>
#include <algorithm>
    
using namespace std;
    
int main() {
    int r, s, p; cin >> r >> s >> p;
    vector<int>v;
    for(int i = 0; i < p; i++) {
        int x, y; cin >> x >> y;
        if(y <= s) {
            v.push_back(r - x + 1 + s - y + 1);
        } else {
            v.push_back(r - x + 1 + y - s);
        }
    }
    sort(v.begin(), v.end());
    int t = 0;
    for(int i = 1; i < (int)v.size(); i++) {
        v[i] = max(v[i], v[i - 1] + 1);
    }
    cout << v.back() << '\n';
}
