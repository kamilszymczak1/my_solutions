#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    string s; cin >> s;
    
    n = 1 << n;
    
    vector<int>meetingOrder(n / 2 - 1);
    for(int i = 0; i < n / 2 - 1; i++)
        meetingOrder[i] = i;
    
    vector<bool>decision;
    for(char c : s)
        decision.push_back(c == 'A' ? 1 : 0);
    
    int sum = 0;
    do {
        vector<bool>currentDecision = decision;
        for(int x : meetingOrder) {
            int a = currentDecision[x * 2 + 1];
            int b = currentDecision[x * 2 + 2];
            int c = currentDecision[x];
            if(a + b + c >= 2) {
                currentDecision[x] = 1;
            } else {
                currentDecision[x] = 0;
            }
        }
        sum += currentDecision[0];
    } while(next_permutation(meetingOrder.begin(), meetingOrder.end()));
    
    int factorial = 1;
    for(int i = 1; i <= n / 2 - 1; i++)
        factorial *= i;
    
    cout << fixed << setprecision(10) << (long double)sum / factorial << '\n';
    
}
