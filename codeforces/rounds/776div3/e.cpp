#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void TestCase() {
    int n, d, last = 0; scanf("%d%d", &n, &d);
    vector<int>a(n), rest(n);
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        rest[i] = a[i] - last - 1;
        last = a[i];
    }
    
    vector<int>minRestPref(n), minRestSuff(n);
    minRestPref[0] = rest[0];
    for(int i = 1; i < n; i++)
        minRestPref[i] = min(rest[i], minRestPref[i - 1]);
    minRestSuff[n - 1] = rest[n - 1];
    for(int i = n - 2; i >= 0; i--)
        minRestSuff[i] = min(rest[i], minRestSuff[i + 1]);
    
    int result = minRestPref[n - 1];
    for(int i = 0; i < n - 1; i++) {
        int localResult = 1 << 30;
        if(i > 0)
            localResult = min(localResult, minRestPref[i - 1]);
        if(i < n - 2)
            localResult = min(localResult, minRestSuff[i + 2]);
        localResult = min(localResult, d - a.back() - 1);
        localResult = min(localResult, rest[i + 1] + rest[i] + 1);
        result = max(result, localResult);
    }
    
    result = max(result, min(minRestPref[n - 2], d - a[n - 2] - 1));
    
    int biggest = *max_element(rest.begin(), rest.end());
    for(int i = 0; i < n - 1; i++) {
        int localResult = 1 << 30;
        if(i > 0)
            localResult = min(localResult, minRestPref[i - 1]);
        if(i < n - 2)
            localResult = min(localResult, minRestSuff[i + 2]);
        localResult = min(localResult, (max(biggest, rest[i] + rest[i + 1] + 1) - 1) / 2);
        localResult = min(localResult, rest[i] + rest[i + 1] + 1);
        result = max(result, localResult);
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
