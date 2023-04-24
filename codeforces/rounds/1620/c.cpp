#include <iostream>
#include <vector>

using namespace std;

const long double inf = 3e18 + 7;

void TestCase() {
    int n, k; cin >> n >> k;
    long long x; cin >> x; x--;
    string s; cin >> s;
    vector<long long>v;
    int it = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == 'a') {
            v.push_back(-1);
            continue;
        }
        int j = i;
        while(j < n && s[j] == '*')
            j++;
        v.push_back((j - i) * k + 1);
        i = j - 1;
    }
    
    vector<long long>suffMult(v.size() + 1, 1);
    for(int i = (int)v.size() - 1; i >= 0; i--) {
        if(abs((long double)suffMult[i + 1] * v[i]) > inf) {
            suffMult[i] = inf;
        } else {
            suffMult[i] = abs(suffMult[i + 1] * v[i]);
        }
    }
    
    for(int i = 0; i < (int)v.size(); i++) {
        if(v[i] == -1) {
            cout << 'a';
        } else {
            int bCount = 0;
            while(x >= suffMult[i + 1]) {
                bCount++;
                x -= suffMult[i + 1];
            }
            while(bCount--)
                cout << 'b';
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
