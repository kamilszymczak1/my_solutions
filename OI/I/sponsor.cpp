#include <iostream>
#include <vector>

using namespace std;

vector<vector<float>>V;
vector<float>Max;
int n;
float a;

int binsearch(float a);

int main() {
    ios_base::sync_with_stdio(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a;
        int index = binsearch(a);
        if(index + 1 > V.size()) {
            Max.push_back(a);
            V.push_back(vector<float>(1, a));
        } else {
            Max[index] = max(Max[index],a);
            V[index].push_back(a);
        }
    }
    cout << Max.size() * 100 << "\n";
    return 0;
}

int binsearch(float a ) {
    int beg = 0;
    int end = V.size()-1;
    while(beg <= end) {
        int mid = (beg + end) / 2;
        if(Max[mid] > a) beg = mid + 1;
        else end = mid - 1;
    }
    return beg;
}

/*
20
22.155 23.252 22.586 22.450 23.372 22.228
22.087 23.091 22.190 22.140 22.057 22.123
22.359 22.190 22.140 22.523 22.384 22.488
23.201 23.050
*/
