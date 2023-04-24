#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    string s; cin >> s;
    int n = s.size();
    vector<int>lastOccurence(26, -1), occurenceCnt(26, 0);
    for(int i = 0; i < n; i++) {
        occurenceCnt[s[i] - 'a']++;
        lastOccurence[s[i] - 'a'] = i;
    }
    
    vector<pair<int, char>>letterOrder;
    for(int i = 0; i < 26; i++)
        if(lastOccurence[i] != -1)
            letterOrder.emplace_back(lastOccurence[i], i + 'a');
        sort(letterOrder.begin(), letterOrder.end());
    bool good = true;
    int initLen = 0;
    for(int i = 0; i < letterOrder.size(); i++) {
        char c = letterOrder[i].second;
        if(occurenceCnt[c - 'a'] % (i + 1) != 0)
            good = false;
        initLen += occurenceCnt[c - 'a'] / (i + 1);
    }
    string result = s.substr(0, initLen);
    string newS = "";
    vector<bool>disabled(26, false);
    for(int i = 0; i < letterOrder.size(); i++) {
        for(int j = 0; j < result.size(); j++) {
            if(!disabled[result[j] - 'a']) {
                newS += result[j];
            }
        }
        disabled[letterOrder[i].second - 'a'] = true;
    }
    if(!good || newS != s) {
        cout << "-1\n";
    } else {
        cout << result << ' ';
        for(auto [x, c] : letterOrder)
            cout << c;
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
