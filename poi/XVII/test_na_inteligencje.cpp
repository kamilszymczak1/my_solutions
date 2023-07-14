#include <iostream>
#include <vector>

#define MAX_N 1000001

using namespace std;

vector<int>positions[MAX_N];

void Load();

bool Query(int m);

int main() {
    ios_base::sync_with_stdio(0);
    
    Load();
    
    int n, m;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> m;
        if(Query(m))
            cout << "TAK\n";
        else
            cout << "NIE\n";
    }
     
    return 0;
}

bool Query(int m) {
    int position = 1, val;
    bool result = true;
    for(int i = 0; i < m; i++) {
        cin >> val;
        
        int beg = 0;
        int end = positions[val].size() - 1;
        while(beg <= end) {
            int mid = (beg + end) / 2;
            if(positions[val][mid] >= position)
                end = mid - 1;
            else
                beg = mid + 1;
        }
        
        if(beg == positions[val].size()) 
            result = false;
        
        if(result)
            position = positions[val][beg] + 1;
    }
    return result;
}

void Load() {
    int m, val;
    cin >> m;
    for(int i = 1; i <= m; i++) {
        cin >> val;
        positions[val].push_back(i);
    }
}
