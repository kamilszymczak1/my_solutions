#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Action {
    double a, b;
    int order;
    Action(double aa, double bb, int o) {
        a = aa;
        b = bb;
        order = o;
    }
};

bool Comp(Action a, Action b) {
    if(a.b * b.a == a.a * b.b)
        return a.order < b.order;
    return a.b * b.a < a.a * b.b;
}

int main() {
    ios_base::sync_with_stdio(0);
    
    vector<int>zeropos;
    vector<Action>actions;
    int n, zeroCount = 0;
    long double a, b;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a >> b;
        if(a != b || b != 0)
            actions.push_back(Action(a, b, i + 1));
        else
            zeropos.push_back(i + 1);
    }
    sort(actions.begin(), actions.end(), Comp);
    for(int pos : zeropos)
        cout << pos << "\n";
    for(Action a : actions)
        cout << a.order << "\n";
    
    return 0;
}
