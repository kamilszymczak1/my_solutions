#include "gralib.hpp"
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int MAX_N = 250007;
const long double inf = 1e12;
long double e[MAX_N];
int N, M, K;
vector<int>best[MAX_N];
vector<int>d[MAX_N];

bool Find(int x, int y) {
    int beg = 0, end = best[x].size() - 1;
    while(beg <= end) {
        int mid = (beg + end) >> 1;
        if(best[x][mid] < y)
            beg = mid + 1;
        else
            end = mid - 1;
    }
    return best[x][end + 1] == y;
}

bool Good(int x, int y, int N, int K) {
    return N - x < K || Find(x, y);
}

void Play() {
    for(int x = 0; x != N;) {
        int y = nastepna();
        if(x % y == 0 && x + y <= N && Good(x, y, N, K)) {
            x += y;
            zwieksz();
        }
    }
    koniec();
}

int main() {
    for(int i = 0; i < MAX_N; i++) {
        for(int k = 1; k <= 500; k++) {
            if(i % k == 0) {
                d[i].push_back(k);
            }
        }
    }
    N = dajN(); M = dajM(); K = dajK();
    
    e[N] = 0;
    for(int i = N - 1; i >= 0; i--) {
        vector<pair<long double, int>>v;
        for(int j = 0; j < d[i].size() && d[i][j] <= K && i + d[i][j] <= N; j++) {
            v.emplace_back(e[i + d[i][j]], d[i][j]);
        }
        sort(v.begin(), v.end());
        
        long double bestE = inf, sum = 0;
        int bestPrefix = 0;
        for(int i = 0; i < v.size(); i++) {
            sum += v[i].first;
            long double currentE = (K + sum) / (long double)(i + 1);
            if(currentE < bestE) {
                bestE = currentE;
                bestPrefix = i;
            }
        }
        
        e[i] = bestE;
        
        best[i].clear();
        for(int j = 0; j <= bestPrefix; j++)
            best[i].push_back(v[j].second);
        sort(best[i].begin(), best[i].end());
    }
    
    for(int i = 0; i < 100; i++)
        Play();
    return 0;
}
