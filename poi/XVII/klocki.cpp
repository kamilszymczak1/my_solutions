#include <iostream>

using namespace std;

const int MAX_N = 1000001;
long long pref[MAX_N], arr[MAX_N], maxSuf[MAX_N];
int n, m;

int Query(int k);

int main() {
    ios_base::sync_with_stdio(0);
    
    int k;
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    
    for(int i = 0; i < m; i++) {
        cin >> k;
        cout << Query(k) << " ";
    }
    
    cout << "\n";
    
    return 0;
}

int Query(int k) {
    pref[0] = 0;
    for(int i = 1; i <= n; i++)
        pref[i] = pref[i - 1] + arr[i] - k;
    
    maxSuf[n] = pref[n];
    
    for(int i = n - 1; i >= 0; i--)
        maxSuf[i] = max(pref[i], maxSuf[i + 1]);
    
    int result = 0, end = 1;
    for(int beg = 1; beg <= n; beg++) {
        while(end <= n && maxSuf[end] - pref[beg - 1] >= 0)
            end++;
        result = max(result, end - beg);
    }
    
    return result;
}
