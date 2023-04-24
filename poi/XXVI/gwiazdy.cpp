#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, s; cin >> n >> s; s--;
    
    
    
    vector<int>l(n), r(n);
    for(int i = 0; i < n - 1; i++)
        cin >> l[i] >> r[i];
    vector<long long>bestSuff(n + 1, 0);
    for(int i = n - 2; i >= 0; i--)
        bestSuff[i] = min(l[i], r[i]) + bestSuff[i + 1];
    
    if(n == 2) {
        if(s == 1) {
            cout << l[0] << '\n';
            cout << "2 1\n";
        } else {
            cout << r[0] << '\n';
            cout << "1 2\n";
        }
        return 0;
    }
    
    //what if I go only to the right at first
    long long bestResultRight = 1ll << 60, taken = r[0], bestR = 1;
    for(int i = 1; i < min(n, n - s); i++) {
        long long currentResult = taken + l[i] + bestSuff[i + 1];
        if(currentResult < bestResultRight) {
            bestR = i;
            bestResultRight = currentResult;
        }
        taken += r[i];
    }
    
    taken = l[0];
    long long bestResultLeft = 1ll << 60, bestL = 1;
    
    //what if I go only to the left
    for(int i = 1; i <= min(n - 1, s); i++) {
        long long currentResult = taken + r[i] + bestSuff[i + 1];
        if(currentResult < bestResultLeft) {
            bestL = i;
            bestResultLeft = currentResult;
        }
        taken += l[i];
    }
    
    long long result = min(bestResultLeft, bestResultRight);
    
    int position = s, p = 0;
    vector<int>ans(1, s);
    set<int>planets;
    for(int i = 0; i < n; i++)
        planets.insert(i);
    planets.erase(planets.find(s));
    
    if(bestResultLeft < bestResultRight) { //it is optimal to go to the right first
        for(int i = 0; i < bestL; i++) {
            if(i == bestL - 1)
                position = 0;
            else 
                position--;
            planets.erase(planets.find(position));
            ans.push_back(position);
            p++;
        }
        l[bestL] = 1 << 30;
    } else {
        for(int i = 0; i < bestR; i++) {
            if(i == bestR - 1)
                position = n - 1;
            else
                position++;
            planets.erase(planets.find(position));
            ans.push_back(position);
            p++;
        }
        r[bestR] = 1 << 30;
    }
    
    while(!planets.empty()) {
        int q = p;
        while(q < n - 1 && (l[p] < r[p]) == (l[q] < r[q]))
            q++;
        int len = q - p;
        if(l[p] < r[p]) {
            vector<int>toAdd;
            for(int i = 0; i < len; i++) {
                toAdd.push_back(*planets.begin());
                planets.erase(planets.begin());
            }
            reverse(toAdd.begin(), toAdd.end());
            for(int x : toAdd)
                ans.push_back(x);
        } else {
            vector<int>toAdd;
            for(int i = 0; i < len; i++) {
                auto it = planets.end(); it--;
                toAdd.push_back(*it);
                planets.erase(it);
            }
            reverse(toAdd.begin(), toAdd.end());
            for(int x : toAdd)
                ans.push_back(x);
        }
        p = q;
    }
    
    
    long long localResult = 0;
    for(int i = 0; i < n - 1; i++) {
        if(ans[i + 1] > ans[i]) {
            localResult += r[i];
        } else {
            localResult += l[i];
        }
    }
    
    cout << result << '\n';
    for(int x : ans)
        cout << x + 1 << ' ';
    cout << '\n';
    
    return 0;
}
