#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <deque>
#include <cassert>

using namespace std;

void scale(vector<int>&a) {
    vector<int>b = a;
    sort(b.begin(), b.end());
    map<int, int>m;
    for(int i = 0; i < (int)a.size(); i++)
        m[b[i]] = i;
    for(int &x : a)
        x = m[x];
}

int main() {
    int n; cin >> n;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    scale(a);
    int mx_length = 1;
    vector<vector<int>>cycles;
    vector<bool>visited(n, false);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            cycles.emplace_back();
            for(int j = i; !visited[j]; j = a[j]) {
                cycles.back().emplace_back(j);
                visited[j] = true;
            }
            mx_length = max(mx_length, (int)cycles.back().size());
        }
    }
    if(mx_length == 1) {
        cout << "0\n";
        return 0;
    }
    
    if(mx_length == 2) {
        cout << "1\n";
        deque<int>d;
        for(vector<int>v : cycles) {
            if(v.size() == 2) {
                d.push_front(v[0]);
                d.push_back(v[1]);
            }
        }
        cout << d.size() << '\n';
        for(int x : d)
            cout << x + 1 << ' ';
        cout << '\n';
        return 0;
    }
    
    cout << "2\n";
    deque<int>d;
    for(vector<int>v : cycles) {
        int mid = ((int)v.size() - 1) / 2;
        for(int i = 1; i <= ((int)v.size() - 1) / 2; i++) {
            d.push_front(v[mid - i]);
            d.push_back(v[mid + i]);
            swap(a[v[mid - i]], a[v[mid + i]]);
        }
    }
    cout << d.size() << '\n';
    for(int x : d)
        cout << x + 1 << ' ';
    cout << '\n';
    
    mx_length = 1;
    cycles.clear();
    fill(visited.begin(), visited.end(), false);
    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            cycles.emplace_back();
            for(int j = i; !visited[j]; j = a[j]) {
                cycles.back().emplace_back(j);
                visited[j] = true;
            }
            mx_length = max(mx_length, (int)cycles.back().size());
        }
    }
    
    assert(mx_length == 2);
    
    d.clear();
    for(vector<int>v : cycles) {
        if(v.size() == 2) {
            d.push_front(v[0]);
            d.push_back(v[1]);
        }
    }
    cout << d.size() << '\n';
    for(int x : d)
        cout << x + 1 << ' ';
    cout << '\n';
    return 0;
    
    return 0;
}
