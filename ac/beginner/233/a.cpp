#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int x, y; cin >> x >> y;
    string s; cin >> s;
    for(int i = x - 1; i < (x + y) / 2; i++)
        swap(s[i], s[y - i + x - 2]);
    cout << s << '\n';
    
    return 0;
}
