#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<int>v(n), firstOccurrence(n, -1);
    int diffCount = 0;
    for(int i = 0; i < n; i++) {
        cin >> v[i]; v[i]--;
        if(firstOccurrence[v[i]] == -1) {
            diffCount++;
            firstOccurrence[v[i]] = i;
        }
    }
    
    if(diffCount < k) {
        cout << "-1\n";
        return 0;
    }
    
    sort(firstOccurrence.begin(), firstOccurrence.end());
    long long result = 0;
    int j = find(firstOccurrence.begin(), firstOccurrence.end(), 0) - firstOccurrence.begin();
    for(int i = 0; i < k; i++)
        result += firstOccurrence[i + j] - i;
    cout << result << '\n';
    
    return 0;
}
