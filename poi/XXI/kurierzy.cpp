#include <iostream>
#include <vector>

#define MAX_N 500000

using namespace std;

const int leafCount = 1 << 19;
int tree[leafCount * 2];

vector<int>positions[MAX_N + 1];
int n, m;

void ReadData();
int CalcInRange(int a, int b, int val);
void MakeTree(int a, int b, int lo, int hi, int i);
int Query(int a, int b, int lo, int hi, int i);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    MakeTree(0, n, 0, leafCount, 1);
    
    int a, b;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        cout << Query(a - 1, b, 0, leafCount, 1) << "\n";
    }
    
    return 0;
}

int Query(int a, int b, int lo, int hi, int i) {
    if(a == lo && b == hi)
        return tree[i];
    if(a >= b)
        return 0;
    int mid = (lo + hi) / 2;
    int first = Query(a, min(mid, b), lo, mid, i * 2);
    int second = Query(max(a, mid), b, mid, hi, i * 2 + 1);
    if(CalcInRange(a, b - 1, first) * 2 > b - a)
        return first;
    if(CalcInRange(a, b - 1, second) * 2 > b - a)
        return second;
    return 0;
}

void MakeTree(int a, int b, int lo, int hi, int i) {
    if(a >= b || (b - a == 1 && i >= leafCount))
        return;
    int mid = (lo + hi) / 2;
    MakeTree(a, min(mid, b), lo, mid, i * 2);
    MakeTree(max(a, mid), b, mid, hi, i * 2 + 1);
    if(CalcInRange(a, b - 1, tree[i * 2]) * 2 > b - a)
        tree[i] = tree[i * 2];
    else if(CalcInRange(a, b - 1, tree[i * 2 + 1]) * 2 > b - a)
        tree[i] = tree[i * 2 + 1];
}

void ReadData() {
    int val;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> val;
        tree[i + leafCount] = val;
        positions[val].push_back(i);
    }
}

int CalcInRange(int a, int b, int val) {
    if(val < 1)
        return 0;
    int beg1 = 0, end1 = positions[val].size() - 1;
    while(beg1 <= end1) {
        int mid = (beg1 + end1) / 2;
        if(positions[val][mid] >= a)
            end1 = mid - 1;
        else
            beg1 = mid + 1;
    }
    int beg2 = 0, end2 = positions[val].size() - 1;
    while(beg2 <= end2) {
        int mid = (beg2 + end2) / 2;
        if(positions[val][mid] > b)
            end2 = mid - 1;
        else
            beg2 = mid + 1;
    }
    return beg2 - beg1;
}
