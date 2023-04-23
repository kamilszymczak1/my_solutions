#include <iostream>
#include <vector>

using namespace std;


long long cnt[22][6];
vector<int>adj[6];

int Calc(int a, int b) {
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(0);
    adj[1].push_back(4);
    adj[2].push_back(0);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(5);
    adj[4].push_back(0);
    adj[4].push_back(5);
    adj[5].push_back(4);
    adj[5].push_back(3);
    cnt[0][0] = 1;
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 6; j++) {
            for(int k : adj[j]) {
                cnt[i + 1][k] += cnt[i][j];
            }
        }
    }
    cout << cnt[20][0] << '\n';
}

int main() {
    Calc(0, 0);
    
    return 0;
}
