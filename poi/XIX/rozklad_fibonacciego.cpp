#include <iostream>
#include <vector>

#define inf 1000000000000000000

using namespace std;

vector<long long>fib;

void FindFib();

long long FindClosest(long long val);

int main() {
    ios_base::sync_with_stdio(0);
    FindFib();
    
    int p;
    cin >> p;
    
    while(p--) {
        int result = 0;
        long long val;
        cin >> val;
        while(val != 0) {
            long long closest = FindClosest(abs(val));
            if(val < 0)
                val += closest;
            else
                val -= closest;
            
            result++;
        }
            
        cout << result << "\n";
    }
    
    return 0;
}

long long FindClosest(long long val) {
    int beg = 0;
    int end = fib.size() - 1;
    while(beg <= end) {
        int mid = (beg + end) / 2;
        if(fib[mid] < val)
            beg = mid + 1;
        else
            end = mid - 1;
    }
    if(beg != 0 && abs(fib[beg - 1] - val) < abs(fib[beg] - val))
        beg--;
    return fib[beg];
}

void FindFib() {
    fib.push_back(1);
    fib.push_back(1);
    long long next;
    do {
        int i = fib.size();
        next = fib[i - 1] + fib[i - 2];
        fib.push_back(next);
    } while(next < inf);
}
