#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include <bitset>
#include <map>
#include <queue>
#include <cstring>
#include <cmath>

using namespace std;

struct SegTree {
    vector<long long>values;
    int leafCount;
    SegTree(vector<long long>a) {
        int n = a.size();
        for(leafCount = 1; leafCount < n; leafCount *= 2) {}
        values.resize(leafCount * 2);
        for(int i = 0; i < n; i++)
            values[i + leafCount] = a[i];
        for(int i = leafCount - 1; i > 1; i--)
            values[i] = max(values[i * 2], values[i * 2 + 1]);
    }
    long long GetMax(int a, int b) {
        a += leafCount;
        b += leafCount;
        long long result = max(values[a], values[b]);
        while(a / 2 != b / 2) {
            if(a % 2 == 0)
                result = max(result, values[a + 1]);
            if(b % 2 == 1)
                result = max(result, values[b - 1]);
            a /= 2;
            b /= 2;
        }
        return result;
    }
};

void TestCase() {
    int n; scanf("%d", &n);
    long long m; scanf("%lld", &m);
    vector<long long>x(n), p(n), allX;
    for(int i = 0; i < n; i++) {
        scanf("%lld", &x[i]);
        scanf("%lld", &p[i]);
        allX.push_back(x[i]);
        allX.push_back(x[i] - p[i]);
        allX.push_back(x[i] + p[i]);
    }
    sort(allX.begin(), allX.end());
    allX.resize(unique(allX.begin(), allX.end()) - allX.begin());
    
    vector<long long>rateChange(allX.size() + 1), l(n), r(n), mid(n);
    for(int i = 0; i < n; i++) {
        l[i] = lower_bound(allX.begin(), allX.end(), x[i] - p[i]) - allX.begin();
        r[i] = lower_bound(allX.begin(), allX.end(), x[i] + p[i]) - allX.begin();
        mid[i] = lower_bound(allX.begin(), allX.end(), x[i]) - allX.begin();
        rateChange[l[i]]++;
        rateChange[mid[i]] -= 2;
        rateChange[r[i]]++;
    }
    long long rate = 0;
    long long current = 0;
    vector<long long>rain(allX.size());
    for(int i = 0; i < allX.size(); i++) {
        rain[i] = current;
        rate += rateChange[i];
        if(i < (int)allX.size() - 1)
            current = current + rate * (allX[i + 1] - allX[i]);
    }
    
    vector<long long>rain2 = rain, rain3 = rain;
    
    for(int i = 0; i < allX.size(); i++) {
        rain2[i] -= allX[i];
        rain3[i] += allX[i];
    }
    
    SegTree T1(rain), T2(rain2), T3(rain3);
    
    for(int i = 0; i < n; i++) {
        bool answer = true;
        
        long long C = max(T1.GetMax(0, l[i]), T1.GetMax(r[i], (int)allX.size() - 1));
        long long A = T2.GetMax(l[i], mid[i]);
        long long B = T3.GetMax(mid[i], r[i]);
        
        if(A - p[i] + x[i] > m)
            answer = false;
        if(B - p[i] - x[i] > m)
            answer = false;
        if(C > m)
            answer = false;
        
        if(answer)
            printf("1");
        else
            printf("0");
    }
    printf("\n");
}

int main() {
    int t; scanf("%d", &t);
    while(t--)
        TestCase();
    return 0;
}
