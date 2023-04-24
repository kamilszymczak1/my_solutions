#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n; cin >> n;
    vector<int>s;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x == 1) {
            s.push_back(1);
        } else {
            while(s.back() + 1 != x)
                s.pop_back();
            s.back()++;
        }
        for(int i = 0; i < s.size(); i++) {
            if(i != 0)
                cout << ".";
            cout << s[i];
        }
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
