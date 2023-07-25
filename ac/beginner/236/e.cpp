#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

bool CheckAverage(vector<int>&a, long double required) {
    long double dp0 = 0, dp1 = 0;
    for(int x : a) {
        long double newDp1 = max(dp0, dp1) + x - required;
        dp0 = dp1;
        dp1 = newDp1;
    }
    return max(dp0, dp1) >= 0;
}

double FindMaxAverage(vector<int>&a) {
    long double l = 1, r = 1e9 + 1;
    while(r - l > 1e-7) {
        long double mid = (l + r) / 2;
        if(CheckAverage(a, mid)) {
            l = mid;
        } else {
            r = mid;
        }
    }
    return (l + r) / 2;
}

bool CheckMedian(vector<int>&a, int required) {
    int n = a.size(), greaterCnt = 0, smallerTaken = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] >= required) {
            greaterCnt++;
        } else {
            int j = i;
            while(j < n - 1 && a[j + 1] < required)
                j++;
            smallerTaken += (j - i + 1) / 2;
            i = j;
        }
    }
    return smallerTaken < greaterCnt;
}

int FindMaxMedian(vector<int>&a) {
    int result = 0;
    for(int i = 29; i >= 0; i--) {
        if(CheckMedian(a, result + (1 << i))) {
            result += 1 << i;
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    cout << fixed << setprecision(7) << FindMaxAverage(a) << '\n' << FindMaxMedian(a) << '\n';
    
    return 0;
}
