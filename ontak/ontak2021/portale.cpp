#include "cporlib.h"
#include <vector>

using namespace std;

int main() {
    int n = dajN(), d = dajD(), m = dajM();
    vector<int>h(n + 1, -1);
    const int maxHeight = d / 2;
    pair<int, int>p = zalamanie();
    portal();
    h[p.first] = 1; h[p.second] = 2;
    for(int components = n -1; components > 1;) {
        p = zalamanie();
        if(h[p.first] > h[p.second])
            swap(p.first, p.second);
        if(h[p.first] == -1 && h[p.second] != -1 && h[p.second] <= maxHeight) {
            h[p.first] = h[p.second] + 1;
            portal();
            components--;
        }
    }
    return 0;
}
