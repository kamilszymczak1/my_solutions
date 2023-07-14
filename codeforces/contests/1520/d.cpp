#include <iostream>
#include <algorithm>

using namespace std;

const int MAX_N = 200007;

int a[MAX_N], n;

void TestCase() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= i;
    }
    sort(a, a + n);
    long long result = 0;
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && a[i] == a[j])
            j++;
        long long len = j - i;
        result += len * (len - 1) / 2;
        i = j - 1;
    }
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        TestCase();
    }
    return 0;
}

