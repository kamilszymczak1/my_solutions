#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n; cin >> n;
    string result = "";
    vector<int>js;
    for(int i = 1; i <= 9; i++) {
        if(n % i == 0) {
            js.push_back(i);
        }
    }
    for(int i = 0; i <= n; i++) {
        bool added = false;
        for(int j : js) {
            if(i % (n / j) == 0) {
                result += (char)(j + '0');
                added = true;
                break;
            }
        }
        if(!added) {
            result += '-';
        }
    }
    cout << result << '\n';
    return 0;
}
