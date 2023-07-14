#include <iostream>
#include <vector>

using namespace std;

void TestCase() {
    int n, k; cin >> n >> k;
    vector<int>match(2 * n, -1);
    for(int i = 0; i < k; i++) {
        int a, b; cin >> a >> b;
        match[a - 1] = b - 1;
        match[b - 1] = a - 1;
    }
    vector<int>unmatched;
    for(int i = 0; i < n * 2; i++)
        if(match[i] == -1)
            unmatched.push_back(i);
        int m = unmatched.size();
    for(int i = 0; i < m / 2; i++) {
        match[unmatched[i]] = unmatched[i + m / 2];
        match[unmatched[i + m / 2]] = unmatched[i];
    }
    
    int result = 0;
    for(int i = 0; i < n * 2; i++) {
        for(int j = 0; j < n * 2; j++) {
            pair<int, int>A = {i, match[i]};
            pair<int, int>B = {j, match[j]};
            if(A.first > A.second)
                swap(A.first, A.second);
            if(B.first > B.second)
                swap(B.first, B.second);
            if(A.first > B.first)
                swap(A, B);
            if(A.first < B.first && B.first < A.second && A.second < B.second)
                result++;
        }
    }
    cout << result / 8 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
