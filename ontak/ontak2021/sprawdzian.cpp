#include "sprlib.hpp"
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <numeric>

using namespace std;

int Mid(pair<int, int>p) {
    return (p.first + p.second) / 2 + ((p.first + p.second) % 2 != 0);
}

void FillToLeft(int index, vector<int>&unknown, vector<pair<int, int>>&interval, bool up) {
    if(index == -1)
        return;
    int x = unknown[index];
    int mid = Mid(interval[x]);
    if(up) {
        interval[x].first = mid;
    } else {
        interval[x].second = mid - 1;
    }
    FillToLeft(index - 1, unknown, interval, !up);
}

void TestCase() {
    int n = dajN();
    vector<pair<int, int>>interval(n, make_pair(0, n));
    vector<int>ans(n, -1), unknown(n);
    iota(unknown.begin(), unknown.end(), 0);
    
    while(unknown.size() > 0) {
        random_shuffle(unknown.begin(), unknown.end());
        bool found = false;
        for(int i = 0; i < unknown.size() - 1 && !found; i++) {
            vector<int>difficulty(n, n + 1);
            int a = unknown[i], b = unknown[i + 1];
            difficulty[a] = Mid(interval[a]);
            difficulty[b] = Mid(interval[b]);
            int k = tura(difficulty), status = 0;
            if(k == 0) {
                interval[a].second = Mid(interval[a]) - 1;
                interval[b].second = Mid(interval[b]) - 1;
                FillToLeft(i - 1, unknown, interval, 1);
                found = true;
            } else if(k == 2) {
                interval[a].first = Mid(interval[a]);
                interval[b].first = Mid(interval[b]);
                FillToLeft(i - 1, unknown, interval, 0);
                found = true;
            }
        }
        
        if(!found) {
            int a = unknown.back();
            vector<int>difficulty(n, n + 1);
            difficulty[a] = Mid(interval[a]);
            if(tura(difficulty)) {
                interval[a].first = Mid(interval[a]);
                FillToLeft(unknown.size() - 2, unknown, interval, 0);
            } else {
                interval[a].second = Mid(interval[a]) - 1;
                FillToLeft(unknown.size() - 2, unknown, interval, 1);
            }
        }
        
        unknown.clear();
        for(int i = 0; i < n; i++) {
            if(interval[i].first == interval[i].second) {
                ans[i] = interval[i].first;
            } else {
                unknown.push_back(i);
            }
        }
    }
    koniec(ans);
}

int main() {
    srand(time(NULL));
    for(int i = 0; i < 10; i++)
        TestCase();
    return 0;
}
