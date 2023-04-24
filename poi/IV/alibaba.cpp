#include <iostream>
#include <queue>

#define SIZE 101

using namespace std;

bool visited[SIZE][SIZE][SIZE];

struct Info {
    int amount[3];
    int dist;
    Info() {
        dist = 0;
        for(int i = 0; i < 3; i++)
            amount[i] = 0;
    }
    Info(int *arr) {
        for(int i = 0; i < 3; i++)
            amount[i] = arr[i];
        dist = 0;
    }
};

int Query();
bool Opens(Info &f);
Info LoadInfo();

Info require, take[10], give[10];

int main() {
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    while(n--) {
        int result = Query();
        if(result == -1)
            cout << "NIE\n";
        else
            cout << result << "\n";
    }
}

int Query() {
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            for(int k = 0; k < SIZE; k++)
                visited[i][j][k] = false;
    
    Info start = LoadInfo();
    require = LoadInfo();
    
    int z;
    cin >> z;
    for(int i = 0; i < z; i++) {
        take[i] = LoadInfo();
        give[i] = LoadInfo();
    }
    
    if(Opens(start))
        return 0;
    
    queue<Info>q;
    q.push(start);
    visited[start.amount[0]][start.amount[1]][start.amount[2]] = true;
    
    while(!q.empty()) {
        Info f = q.front();
        q.pop();
        
        Info newInfo;
        newInfo.dist = f.dist + 1;
        
        
        for(int i = 0; i < z; i++) {
            bool go = true;
            for(int j = 0; j < 3; j++) {
                newInfo.amount[j] = f.amount[j] + give[i].amount[j] - take[i].amount[j];
                if(f.amount[j] - take[i].amount[j] < 0 || newInfo.amount[j] >= SIZE)
                    go = false;
            }
            
            
            if(go && !visited[newInfo.amount[0]][newInfo.amount[1]][newInfo.amount[2]]) {
                if(Opens(newInfo))
                    return newInfo.dist;
                q.push(newInfo);
                visited[newInfo.amount[0]][newInfo.amount[1]][newInfo.amount[2]] = true;
            }
        }
    }
    return -1;
}

Info LoadInfo() {
    Info result;
    for(int i = 0; i < 3; i++)
        cin >> result.amount[i];
    return result;
}

bool Opens(Info &f) {
    for(int i = 0; i < 3; i++)
        if(f.amount[i] < require.amount[i])
            return false;
    return true;
}
