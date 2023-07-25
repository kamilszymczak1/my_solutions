#include <iostream>
    
using namespace std;
    
int string_to_int(string s) {
    int result = 0;
    for(char c : s)
        result = result * 10 + c - '0';
    return result;
}
    
int main() {
    ios_base::sync_with_stdio(0);
    string x, y, z, t; cin >> x >> y >> z >> t;
    int a = 0, b = 0;
    if(x == "AD") {
        a = string_to_int(y);
    } else {
        a = -string_to_int(x) + 1;
    }
    
    if(z == "AD") {
        b = string_to_int(t);
    } else {
        b = -string_to_int(z) + 1;
    }
    
    cout << abs(a - b) << '\n';
    
    return 0;
}
