#include <iostream>
#include <vector>

using namespace std;

int Query(int a, int b, int c) {
    cout << "? " << a << ' ' << b << ' ' << c << '\n' << flush;
    int t; cin >> t;
    return t;
}

void TestCase() {
    int n; cin >> n;
    int ind[2] = {-1, -1};
    vector<bool>type(n / 3, false);
    for(int i = 1; i <= n; i += 3) {
        int t = Query(i, i + 1, i + 2);
        ind[t] = i;
        type[i / 3] = t;
    }
    
    int zeroIndex = -1, oneIndex = -1;
    for(int i = 0; i < 3; i++) {
        int t = Query(ind[0], ind[0] + 1, ind[1] + i);
        if(t == 1)
            zeroIndex = ind[0] + 2;
        t = Query(ind[1], ind[1] + 1, ind[0] + i);
        if(t == 0)
            oneIndex = ind[1] + 2;
    }
    if(zeroIndex == -1)
        zeroIndex = ind[0];
    if(oneIndex == -1)
        oneIndex = ind[1];
    
    vector<int>ans;
    for(int i = 0; i < n / 3; i++) {
        int j = i * 3 + 1;
        if(type[i] == 0) {
            if(Query(j, j + 1, oneIndex) == 0) {
                ans.push_back(j);
                ans.push_back(j + 1);
                if(Query(j + 1, j + 2, oneIndex) == 0)
                    ans.push_back(j + 2);
            } else {
                ans.push_back(j + 2);
                if(Query(j, j + 2, oneIndex) == 0) {
                    ans.push_back(j);
                } else {
                    ans.push_back(j + 1);
                }
            }
        } else {
            if(Query(j, j + 1, zeroIndex) == 1) {
                if(Query(j, j + 2, zeroIndex) == 0) {
                    ans.push_back(j + 2);
                }
            } else {
                if(Query(j, j + 2, zeroIndex) == 0) {
                    ans.push_back(j);
                } else {
                    ans.push_back(j + 1);
                }
            }
        }
    }
    
    cout << "! " << ans.size() << " ";
    for(int i = 0; i < (int)ans.size(); i++)
        cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    return 0;
}
