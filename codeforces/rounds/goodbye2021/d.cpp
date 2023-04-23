#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;


struct SegTree {
    vector<int>values;
    int leafCount;
    SegTree(int size, int f) {
        for(leafCount = 1; leafCount < size; leafCount *= 2) {}
        values.resize(leafCount * 2, f);
    }
    int MaxSuffix(int x) {
        if(x >= leafCount)
            return -1;
        int result = values[x + leafCount];
        for(x += leafCount; x; x /= 2)
            if(x % 2 == 0)
                result = max(result, values[x + 1]);
        return result;
    }
    void Set(int x, int value) {
        for(x += leafCount; x; x /= 2)
            values[x] = value;
    }
};

void Scale(vector<long long>&a) {
    int n = a.size();
    vector<long long>b(a.begin(), a.end());
    sort(b.begin(), b.end());
    for(int i = 0; i < n; i++)
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
}


void TestCase() {
    int n; cin >> n;
    vector<long long>A(n + 1);
    for(int i = 1; i <= n; i++)
        cin >> A[i];
    long long x; cin >> x;
    long long sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += A[i];
        A[i] = sum - i * x;
    }
    Scale(A);
    SegTree T(n + 1, -10);
//     cout << "A = ";
//     for(auto x : A)
//         cout << x << ' ';
//     cout << '\n';
    int lastPlaced = 0, placed = 0;
    for(int i = 1; i <= n; i++) {
        int nearestEnd = T.MaxSuffix(A[i] + 1);
        //cout << "nearest End = " << nearestEnd << '\n';
        if(nearestEnd + 1 > lastPlaced) {
            //cout << "placing at " << i << '\n';
            lastPlaced = i;
            placed++;
        }
        T.Set(A[i - 1], i - 1);
       // cout << "Set at " << A[i - 1] << " to " << i - 1 << '\n';
    }
    cout << n - placed << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
