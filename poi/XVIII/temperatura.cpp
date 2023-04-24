#include <iostream>

#define MAX_N 1000000
#define inf 2000000000

using namespace std;

const int leafCount = 1 << 20;
int tree[leafCount * 2];

int hi[MAX_N], lo[MAX_N], range[MAX_N];
int n;

void ReadData();
void MakeTree();
int GetMax(int a, int b);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    MakeTree();
    
    int end = 0, result = 0;
    for(int beg = 0; end < n; beg++) {
        int current = GetMax(beg, end);
        while(end < n && hi[end] >= current) {
            current = max(lo[end], current);
            end++;
        }
        result = max(end - beg, result);
    }
    
    cout << result << "\n";
    
    return 0;
}

int GetMax(int a, int b) {
    a += leafCount;
    b += leafCount;
    int result = max(tree[a], tree[b]);
    while(a / 2 != b / 2) {
        if(a % 2 == 0)
            result = max(result, tree[a + 1]);
        if(b % 2 == 1)
            result = max(result, tree[b - 1]);
        a >>= 1;
        b >>= 1;
    }
    return result;
}

void MakeTree() {
    for(int i = 0; i < n; i++)
        tree[i + leafCount] = lo[i];
    for(int i = n; i < leafCount; i++)
        tree[i + leafCount] = -inf;
    for(int i = leafCount - 1; i > 0; i--)
        tree[i] = max(tree[i * 2], tree[i * 2 + 1]);
}

void ReadData() {
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> lo[i] >> hi[i];
}
