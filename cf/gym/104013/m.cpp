    #include <iostream>
    #include <vector>
    #include <algorithm>
     
    using namespace std;
     
    int main() {
        ios_base::sync_with_stdio(0);
        int n; cin >> n;
        vector<long long>v(n);
        for(int i = 0; i < n; i++)
            cin >> v[i];
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
        n = v.size();
        long long d = v[0];
        for(int i = 0; i < n - 1; i++)
            d = max(v[i + 1] - v[i], d);
        if(v[1] <= d) {
            cout << "0\n";
            return 0;
        }
        for(int i = 0; i < n - 2; i++) {
            if(v[i + 2] - v[i] <= d) {
                cout << "0\n";
                return 0;
            }
        }
        cout << d << '\n';
        return 0;
    }
