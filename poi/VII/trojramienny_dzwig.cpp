#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 400000;

bool used[MAX_N];
int q, p, n;

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    cin >> q >> p >> n;
    vector<int>res[3];
    int x[3];
    
    for(int i = 0; i < n; i++) {
        while(i < n && used[i])
            i++;
        if(i == n)
            break;
        x[0] = x[1] = i, x[2] = i + p + q;
        if(used[i + min(p, q)])
            x[1] += max(p, q);
        else
            x[1] += min(p, q);
        for(int j = 0; j < 3; j++)
            used[x[j]] = true, res[j].push_back(x[j] + 1);
    }
    
    cout << res[0].size() << "\n";
    
    for(int i = 0; i < (int)res[0].size(); i++)
        cout << res[0][i] << " " << res[1][i] << " " << res[2][i] << "\n";
    
    return 0;
}
