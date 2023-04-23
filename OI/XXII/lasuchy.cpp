#include <iostream>
#include <vector>

using namespace std;

vector<int> Solve(vector<int>&c, vector<int>choice) {
    const int n = c.size();
    for(int i = 1; i < n; i++) {
        int leftValue = choice[i - 1] == 1 ? c[i] / 2 : c[i];
        int rightValue = choice[(i + 1) % n] == 0 ? c[(i + 1) % n] / 2 : c[(i + 1) % n];
        choice[i] = leftValue <= rightValue;
    }
    for(int i = n - 1; i > 0; i--) {
        int leftValue = choice[i - 1] == 1 ? c[i] / 2 : c[i];
        int rightValue = choice[(i + 1) % n] == 0 ? c[(i + 1) % n] / 2 : c[(i + 1) % n];
        if(leftValue > rightValue && choice[i] == 1)
            choice[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        int L = (i - 1 + n) % n, R = (i + 1) % n;
        int leftValue = choice[L] == 1 ? c[i] / 2 : c[i];
        int rightValue = choice[R] == 0 ? c[R] / 2 : c[R];
        if(leftValue > rightValue && choice[i] == 1)
            return {};
        if(rightValue > leftValue && choice[i] == 0)
            return {};
    }
    
    vector<int>ans;
    for(int i = 0; i < n; i++)
        ans.push_back((i + choice[i]) % n + 1);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>c(n), taken(n, 0), choice(n, -1);
    for(int &x : c) {
        cin >> x;
        x *= 2;
    }
    
    choice[0] = 0;
    vector<int>ans = Solve(c, choice);
    if(ans.size() == 0) {
        choice[0] = 1;
        ans = Solve(c, choice);
    }
    
    if(ans.size() == 0) {
        cout << "NIE\n";
    } else {
        for(int x : ans)
            cout << x << ' ';
        cout << '\n';
    }
    
    return 0;
}
