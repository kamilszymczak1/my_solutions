#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

void TestCase() {
    int n; scanf("%d", &n);
    vector<int>childCnt(n);
    for(int i = 1; i < n; i++) {
        int p; scanf("%d", &p);
        childCnt[p - 1]++;
    }
    
    vector<int>piles;
    for(int i = 0; i < n; i++) {
        if(childCnt[i] > 0) {
            piles.push_back(childCnt[i]);
        }
    }
    piles.push_back(1);
    
    sort(piles.begin(), piles.end());
    
    vector<int>activePiles;
    int result = 0;
    while(!piles.empty() || !activePiles.empty()) {
        if(piles.empty()) {
            vector<int>activePiles2;
            for(int x : activePiles) {
                if(x > 1) {
                    activePiles2.push_back(x - 1);
                }
            }
            swap(activePiles2, activePiles);
            sort(activePiles.begin(), activePiles.end());
            if(!activePiles.empty()) {
                activePiles.back() -= 1;
                if(activePiles.back() == 0)
                    activePiles.pop_back();
            }
            
        } else {
            vector<int>activePiles2;
            for(int x : activePiles) {
                if(x > 1) {
                    activePiles2.push_back(x - 1);
                }
            }
            swap(activePiles, activePiles2);
            if(piles.back() > 1)
                activePiles.push_back(piles.back() - 1);
            piles.pop_back();
        }
        result++;
    }
    printf("%d\n", result);
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
