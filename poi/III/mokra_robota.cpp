#include <iostream>
#include <queue>

#define MAX_N 4
#define SIZE 6250000

using namespace std;

int powOf50[4] = {1, 50, 50 * 50, 50 * 50 * 50};

bool visited[SIZE];
int capacity[MAX_N];
int targetStatus = 0;
int n;

struct Status {
    int depth;
    int amount[MAX_N];
    Status();
    Status(int *arr, int d);
    int GetVal();
};

Status beginStatus;

void ReadData();
int BFS();
void PourAway(Status &s, queue<Status>&q);
void PourOut(Status &s, queue<Status>&q);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    int result = BFS();
    
    if(result == -1)
        cout << "NIE\n";
    else
        cout << result << "\n";
    
    return 0;
}

int BFS() {
    int temp[MAX_N];
    queue<Status>q;
    visited[beginStatus.GetVal()] = true;
    q.push(beginStatus);
    
    int count = 0;
    
    while(!q.empty()) {
        Status f = q.front();
        q.pop();
        
        count++;
        
        int val = f.GetVal();
        if(f.GetVal() == targetStatus)
            return f.depth;
        
        PourAway(f, q);
        PourOut(f, q);
    }
    
    return -1;
}

void PourOut(Status &s, queue<Status>&q) {
    for(int i = 0; i < n; i++) {
        if(s.amount[i] == capacity[i])
            continue;
        for(int j = 0; j < n; j++) {
            if(i == j || s.amount[j] == 0)
                continue;
            int delta = min(s.amount[j], capacity[i] - s.amount[i]);
            s.amount[i] += delta;
            s.amount[j] -= delta;
            s.depth++;
            if(!visited[s.GetVal()]) {
                visited[s.GetVal()] = true;
                q.push(s);
            }
            s.depth--;
            s.amount[i] -= delta;
            s.amount[j] += delta;
        }
    }
}

void PourAway(Status &s, queue<Status>&q) {
    int val = s.GetVal(), temp = 0;
    for(int i = 0; i < n; i++) {
        if(s.amount[i] == 0)
            continue;
        int newVal = val - s.amount[i] * powOf50[i];
        swap(temp, s.amount[i]);
        if(!visited[newVal]) {
            visited[newVal] = true;
            q.push(Status(s.amount, s.depth + 1));
        }
        swap(temp, s.amount[i]);
    }
}

void ReadData() {
    int val;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> capacity[i];
    beginStatus = Status(capacity, 0);
    
    for(int i = 0; i < n; i++) {
        cin >> val;
        targetStatus += val * powOf50[i];
    }
}

Status::Status(int *arr, int d) {
    depth = d;
    for(int i = 0; i < 4; i++)
        if(arr[i] >= 0 && arr[i] < 50)
            amount[i] = arr[i];
        else
            amount[i] = 0;
}

Status::Status() {
    for(int i = 0; i < 4; i++)
        amount[i] = 0;
}

int Status::GetVal() {
    int result = 0;
    for(int i = 0; i < 4; i++)
        result += amount[i] * powOf50[i];
    return result;
}
