#include <iostream>
#include "task62lib.h"

using namespace std;

const int leafCount = 1 << 14, K = 16;
int tree[leafCount << 1], n, t, k, last = 0;
void AddSuffix(int i, int value) { //how many zeroes are there on suffix
    tree[i += leafCount] += value;
    for(; i; i /= 2) {
        if(!(i & 1))
            tree[i + 1] += value;
    }
}

int ValueAt(int i) {
    int result = 0;
    for(i += leafCount; i; i /= 2)
        result += tree[i];
    return result;
}

int ZeroesAtPrefix(int i) {
    if(i > n)
        return ZeroesAtPrefix(n);
    int sum = PrefixSum(i);
    return i - sum;
}

int FindInRange(int beg, int end) {
    int it = 0;
    while(beg <= end) {
        int mid = (beg + end) >> 1;
        if(ZeroesAtPrefix(mid) < k) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return beg;
}

int main() {
    ios_base::sync_with_stdio(0);
    Init();
    n = GetN();
    t = GetT();
    k = GetQuery();
    for(int i = 1; (i - 1) * K + 1 <= n; i++) {
        last = i;
        int z = PrefixSum(i * K);
        AddSuffix(i, z);
        AddSuffix(i + 1, -z);
    }
    for(int i = 0; i < t; i++) {
        if(i > 0)
            k = GetQuery();
        int beg = 0, end = last;
        while(beg <= end) {
            int mid = (beg + end) / 2;
            if(ValueAt(mid) < k) {
                beg = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        int lastLess = beg - 1;
        int ans = FindInRange(lastLess * K + 1, lastLess * K + K);
        AddSuffix(lastLess + 1, -1);
        Answer(ans);
    }
    return 0;
}
