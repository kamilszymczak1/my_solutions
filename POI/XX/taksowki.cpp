#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

long long NextInt() {
    long long c, result = 0;
    do {
        c = getchar_unlocked();
    } while(!isdigit(c));
    do {
        result = result * 10 + c - '0';
        c = getchar_unlocked();
    } while(isdigit(c));
    return result;
}

int Solve(long long m, long long d, vector<long long>&x) {
    sort(x.begin(), x.end());
    int k = lower_bound(x.begin(), x.end(), m - d) - x.begin();
    if(k == x.size())
        return 0;
    long long X = x[k];
    x.erase(x.begin() + k);
    long long position = 0, index = x.size() - 1;
    while(position * 2 < m + d - X && index >= 0) {
        if(d - position >= x[index])
            return 0;
        position += x[index] - (d - position);
        index--;
    }
    if(position >= m)
        return x.size() - index - 1;
    if(position * 2 >= m + d - X)
        return x.size() - index;
    return 0;
}

int main() {
    long long m = NextInt(), d = NextInt();
    int n = NextInt();
    vector<long long>x(n);
    for(long long &y : x)
        y = NextInt();
    x.push_back(0);
    int result = Solve(m, d, x);
    if(result == -1) {
        cout << "NIE\n";
    } else {
        cout << result << '\n';
    }
    
    return 0;
}
