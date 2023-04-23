#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int Ask(int x, int y, int z) {
    cout << "? " << x << ' ' << y << ' ' << z << '\n' << flush;
    int m; cin >> m;
    return m;
}

void TestCase() {
    int n; cin >> n;
    vector<int>values(n);
    for(int i = 1; i <= n; i++)
        values[i - 1] = i;
    
    int removed = -1;
    while(values.size() >= 3) {
        if(values.size() == 3)
            values.push_back(removed);
        vector<int>x;
        for(int i = 0; i < 4; i++) {
            x.push_back(values.back());
            values.pop_back();
        }
        vector<pair<int, int>>p;
        for(int i = 0; i < 4; i++) {
            vector<int>toAsk;
            for(int j = 0; j < 4; j++) {
                if(i != j) {
                    toAsk.push_back(x[j]);
                }
            }
            p.emplace_back(Ask(toAsk[0], toAsk[1], toAsk[2]), x[i]);
        }
        sort(p.begin(), p.end());
        values.push_back(p[0].second);
        values.push_back(p[1].second);
        removed = p[2].second;
    }
    
    cout << "! " << values[0] << ' ' << values[1] << '\n' << flush;
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
