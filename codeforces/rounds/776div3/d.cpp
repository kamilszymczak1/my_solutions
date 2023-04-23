#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

void Shift(vector<int>&v, int z, int k) {
    int n = v.size();
    k %= z;
    vector<int>t(n);
    for(int i = 0; i < z; i++)
        t[(i - k + z) % z] = v[i];
    v = t;
}

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>a(n);
    for(auto &x : a)
        scanf("%d", &x);
    vector<int>ans;
    for(int i = n - 1; i >= 0; i--) {
        int j = i;
        while(a[j] != i + 1)
            j--;
        int shift = (i + 1 - (i - j)) % (i + 1);
        ans.push_back(shift);
        Shift(a, i + 1, shift);
    }
    reverse(ans.begin(), ans.end());
    for(int x : ans)
        printf("%d ", x);
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    
    return 0;
}
