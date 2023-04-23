#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    const int MAX_N = 1000007;
    vector<vector<int>>factors(MAX_N);
    for(int i = 2; i < MAX_N; i++) {
        if(factors[i].size() == 0) {
            for(int j = i; j < MAX_N; j += i) {
                factors[j].push_back(i);
            }
        }
    }
    vector<bool>possible(MAX_N);
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        possible[x] = true;
    }
    
    int result = 0;
    vector<bool>takenFactor(MAX_N, false);
    for(int i = MAX_N - 1; i >= 1; i--) {
        if(possible[i])
            continue;
        int numbers = 0;
        vector<int>changes;
        for(int j = i + i; j < MAX_N; j += i) {
            if(!possible[j])
                continue;
            numbers++;
            bool good = true;
            for(int factor : factors[j / i]) {
                if(takenFactor[factor] == false) {
                    takenFactor[factor] = true;
                    changes.push_back(factor);
                } else {
                    good = false;
                }
            }
            
            if(numbers > 1 && good) {
                possible[i] = true, result++;
                break;
            }
        }
        for(int x : changes)
            takenFactor[x] = false;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t = 1;
    while(t--)
        TestCase();
    return 0;
}
