#include <iostream>

#define abs(a) a >= 0 ? a : -a

#define MAX_N 10000

using namespace std;

struct DemandInfo {
    long long cost;
    long long dist;
    long long demand;
};

int dist[MAX_N];
int demand[MAX_N];
int n;

int Left(int i);
int Right(int i);

long long DistToLeft(int i);
long long DistToRight(int i);

int FindLastRight();

DemandInfo GetInfoToRight(int beg, int end);
DemandInfo GetInfoToLeft(int beg, int end);

int main() {
    ios_base::sync_with_stdio(0);
    
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> demand[i] >> dist[i];
    
    int lastRight = FindLastRight();
    int lastLeft = Right(lastRight);
    
    DemandInfo rightInfo = GetInfoToRight(0, lastRight);
    DemandInfo leftInfo = GetInfoToLeft(0, lastLeft);
    
    long long result = leftInfo.cost + rightInfo.cost;
    
    for(int i = 1; i < n; i++) {
        leftInfo.dist += DistToLeft(i);
        leftInfo.demand += demand[Left(i)];
        leftInfo.cost += DistToLeft(i) * leftInfo.demand;
        
        rightInfo.dist -= DistToLeft(i);
        rightInfo.cost -= DistToLeft(i) * rightInfo.demand;
        rightInfo.demand -= demand[i];
        
        while(rightInfo.dist + DistToRight(lastRight) < leftInfo.dist) {
            
            rightInfo.dist += DistToRight(lastRight);
            rightInfo.demand += demand[lastLeft];
            rightInfo.cost += rightInfo.dist * demand[lastLeft];
            
            leftInfo.cost -= leftInfo.dist * demand[lastLeft];
            leftInfo.demand -= demand[lastLeft];
            leftInfo.dist -= DistToRight(lastLeft);
            
            lastLeft = Right(lastLeft);
            lastRight = Right(lastRight);
            
        }
        
        result = min(result, leftInfo.cost + rightInfo.cost);
    }
    
    cout << result << "\n";

    return 0;
}

DemandInfo GetInfoToRight(int beg, int end) {
    DemandInfo result = {0, 0, 0};
    while(beg != end) {
        result.dist += DistToRight(beg);
        beg = Right(beg);
        result.demand += demand[beg];
        result.cost += result.dist * demand[beg];
    }
    return result;
}

DemandInfo GetInfoToLeft(int beg, int end) {
    DemandInfo result = {0, 0, 0};
    while(beg != end) {
        result.dist += DistToLeft(beg);
        beg = Left(beg);
        result.demand += demand[beg];
        result.cost += result.dist * demand[beg]; 
    }
    return result;
}

int FindLastRight() {
    int rightDist = 0;
    int leftDist = 0;
    int left = 0;
    int right = 0;
    bool searching = true;
    for(int i = 1; i < n; i++) {
        if(rightDist + DistToRight(right) < leftDist + DistToLeft(left)) {
            rightDist += DistToRight(right);
            right = Right(right);
        } else {
            leftDist += DistToLeft(left);
            left = Left(left);
        }
    }
    return right;
}

long long DistToRight(int i) {
    return dist[i];
}

long long DistToLeft(int i) {
    return dist[Left(i)];
}

int Right(int i) {
    if(i == n - 1)
        return 0;
    return i + 1;
}

int Left(int i) {
    if(i == 0)
        return n - 1;
    return i - 1;
}
