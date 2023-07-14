#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<string>s(n);
    bool one = false;
    for(auto &x : s) {
        cin >> x;
        one |= x.size() == 1;
    }
    if(one) {
        cout << "YES\n";
        return;
    }
    
    for(int i = 0; i < n; i++) {
        if(s[i].size() == 2 && s[i][0] == s[i][1]) {
            cout << "YES\n";
            return;
        } else if(s[i].size() == 3 && s[i][0] == s[i][2]) {
            cout << "YES\n";
            return;
        }
    }
    
    map<string, int>lastOccurence;
    for(int i = 0; i < n; i++) {
        lastOccurence[s[i]] = i;
    }
    
    for(int i = 0; i < n; i++) {
        string t = s[i];
        if(t.size() == 2) {
            string tRev = "..";
            tRev[0] = t[1]; tRev[1] = t[0];
            if(lastOccurence.find(tRev) != lastOccurence.end()) {
                if(lastOccurence[tRev] > i) {
                    cout << "YES\n";
                    return;
                }
            }
            
            tRev = "...";
            tRev[1] = t[1]; tRev[2] = t[0];
            for(char c = 'a'; c <= 'z'; c++) {
                tRev[0] = c;
                if(lastOccurence.find(tRev) != lastOccurence.end()) {
                    if(lastOccurence[tRev] > i) {
                        cout << "YES\n";
                        return;
                    }
                }
            }
        } else {
            string tRev = "..";
            tRev[0] = t[1]; tRev[1] = t[0];
            if(lastOccurence.find(tRev) != lastOccurence.end()) {
                if(lastOccurence[tRev] > i) {
                    cout << "YES\n";
                    return;
                }
            }
            
            tRev = "...";
            tRev[0] = t[2]; tRev[1] = t[1]; tRev[2] = t[0];
            if(lastOccurence.find(tRev) != lastOccurence.end()) {
                if(lastOccurence[tRev] > i) {
                    cout << "YES\n";
                    return;
                }
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
