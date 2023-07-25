#include <iostream>
    
using namespace std;
    
int process() {
    int answer = 0;
    string s; cin >> s >> s >> s >> s;
    if(s == "Yes")
        answer |= 4;
    cin >> s >> s >> s >> s;
    if(s == "Yes")
        answer |= 2;
    cin >> s >> s;
    if(s == "Yes")
        answer |= 1;
    return answer;
}
    
string ans[8] = {
    "x 2 ^ y 2 ^ + ", //000
    "1", //001
    "x y * x 2 ^ + y 3 ^ - x y 2 ^ * -",
    "y x - x 2 ^ + y 3 ^ - x y 2 ^ * -",
    "0 x y * - x 2 ^ - y 3 ^ - x y 2 ^ * -",
    "y x - x 2 ^ - y 3 ^ - x y 2 ^ * -",
    "x 3 ^ y 3 ^ + x 2 ^ y * - x y 2 ^ * -",
    "0 x y * - x 3 ^ + y 3 ^ + x 2 ^ y * - x y 2 ^ * -"
};
    
int main() {
    cout << ans[process()] << '\n';
}
