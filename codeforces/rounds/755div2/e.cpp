#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool Gen(vector<int>current, map<vector<int>, bool>&m) {
    if(m.find(current) != m.end())
        return m[current];
    m[current] = false;
    for(int i = 0; i < (int)current.size() - 1; i++) {
        vector<int>newCurrent = current;
        if(newCurrent[i] > 0 && newCurrent[i + 1] > 0) {
            newCurrent[i]--;
            newCurrent[i + 1]--;
            m[current] |= !Gen(newCurrent, m);
        }
    }
    return m[current];
}

int main() {
    ios_base::sync_with_stdio(0);
    
    map<vector<int>, bool>m;
    const int K = 3;
    for(int i = 0; i <= K; i++) {
        for(int j = 0; j <= K; j++) {
            for(int k = 0; k <= K; k++) {
                for(int l = 0; l <= K; l++) {
                    for(int t = 0; t <= K; t++) {
                        vector<int>current = {i, j, k, l, t};
                        Gen(current, m);
                    }
                }
                
            }
        }
    }
    
    for(auto [v, b] : m) {
        int sum = 0;
        for(int x : v)
            cout << x << ' ', sum += x;
        cout << ": " << b << '\n';
    }
    
    return 0;
}
