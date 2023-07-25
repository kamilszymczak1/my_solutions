#include <iostream>

using namespace std;

int Check(int ind, int scoreA, int scoreB, string &s) {
    if(ind == 10)
        return 10;
    int shootsA = (ind + 1) / 2;
    int shootsB = (ind + 0) / 2;
    int shootsLeftA = 5 - shootsA;
    int shootsLeftB = 5 - shootsB;
    if(scoreA + shootsLeftA < scoreB)
        return ind;
    if(scoreB + shootsLeftB < scoreA)
        return ind;
    
    int result = 10;
    if(ind % 2 == 0) {
        if(s[ind] == '0' || s[ind] == '?')
            result = min(result, Check(ind + 1, scoreA, scoreB, s));
        if(s[ind] == '1' || s[ind] == '?')
            result = min(result, Check(ind + 1, scoreA + 1, scoreB, s));
    } else {
        if(s[ind] == '0' || s[ind] == '?')
            result = min(result, Check(ind + 1, scoreA, scoreB, s));
        if(s[ind] == '1' || s[ind] == '?')
            result = min(result, Check(ind + 1, scoreA, scoreB + 1, s));
    }
    return result;
}

void TestCase() {
    string s; cin >> s;
    cout << Check(0, 0, 0, s) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
