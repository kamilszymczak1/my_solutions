#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <bitset>
#include <queue>
#include <set>
#include <map>

using namespace std;

const long long inf = 1ll << 60;

void test_case() {
    int n; cin >> n;
    vector<long long>v(2 * n);
    for(int i = 0; i < 2 * n; i++)
        cin >> v[i];
    sort(v.begin(), v.end());
    if(n == 1) {
        cout << v[1] - v[0] << '\n';
        return;
    }
    
    long long answer = 0;
    for(int i = 0; i < 2 * n; i++)
        answer += abs(v[i]);
    
    if(n % 2 == 0) {
        long long second_answer = 0;
        for(int i = 0; i < 2 * n - 1; i++)
            second_answer += abs(v[i] + 1);
        second_answer += abs(v[2 * n - 1] - n);
        answer = min(answer, second_answer);
    }
    
    if(n == 2) {
        long long second_answer = 0;
        for(int i = 0; i < 2 * n; i++)
            second_answer += abs(v[i] - 2);
        answer = min(answer, second_answer);
    }
    
    
    cout << answer << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
