#include <iostream>
#include <vector>

using namespace std;

constexpr long long inf = 1e12;

bool Check(long long d, vector<pair<long long, long long>>&intervals, bool print) {
    long long position = -inf;
    for(pair<long long, long long>p : intervals) {
        long long newPosition = max(position + d, p.first);
        if(newPosition > p.second)
            return false;
        position = newPosition;
        if(print)
            cout << position << ' ';
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<pair<long long, long long>>intervals(n);
    for(pair<long long, long long>&p : intervals)
        cin >> p.first >> p.second;
    
    if(!Check(1, intervals, 0)) {
        cout << "NIE\n";
        return 0;
    }
    
    long long beg = 1, end = inf;
    while(beg <= end) {
        long long mid = (beg + end) / 2;
        if(Check(mid, intervals, 0)) {
            beg = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    cout << beg - 1 << '\n';
    Check(beg - 1, intervals, 1);
    cout << '\n';
    return 0;
}
