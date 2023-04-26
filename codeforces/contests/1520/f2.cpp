#include <iostream>

using namespace std;

const int MAX_N = 200007;
const int leafCount = 1 << 18;
int tree[leafCount << 1];
bool known[MAX_N];

int Sum(int x) {
    int result = 0;
    for(x += leafCount; x; x >>= 1)
        result += tree[x];
    return result;
}

void AddSuffix(int x, int value) {
    x += leafCount;
    tree[x] += value;
    for(; x; x >>= 1) {
        if(!(x & 1))
            tree[x + 1] += value;
    }
}

int ZeroesOnPrefix(int x) {
    if(known[x]) {
        return Sum(x);
    }   
    cout << "? " << 1 << ' ' << x << '\n' << flush;
    int sum; cin >> sum;
    int value = Sum(x);
    AddSuffix(x, x - sum - value);
    AddSuffix(x + 1, sum - x + value);
    known[x] = true;
    return x - sum;
}

int main() {
    ios_base::sync_with_stdio(0);
    int n, t; cin >> n >> t;
    for(int i = 0; i < t; i++) {
        int k; cin >> k;
        int beg = 1, end = n;
        while(beg <= end) {
            int mid = (beg + end) >> 1;
            if(ZeroesOnPrefix(mid) < k) {
                beg = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        AddSuffix(beg, -1);
        cout << "! " << beg << '\n' << flush;
    }
}
