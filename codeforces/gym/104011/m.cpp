#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
    
using namespace std;
    
int string_to_int(string s) {
    int result = 0;
    for(char c : s)
        result = result * 10 + c - '0';
    return result;
}
    
long long f(string s) {
    long long result = 0;
    for(char c : s)
        result = result * 30 + c - 'a' + 1;
    return result;
}
    
pair<long long, int> process(string s) {
    int i = 0;
    while(s[i] != '=')
        i++;
    long long t = f(s.substr(0, i));
    int x = string_to_int(s.substr(i + 1, (int)s.size() - i));
    return make_pair(t, x);
}
    
int main() {
    ios_base::sync_with_stdio(0);
    int n; cin >> n;
    int l_sum = 0;
    vector<vector<pair<long long, int>>>tasks(n);
    for(int i = 0; i < n; i++) {
        int l; cin >> l;
        l_sum += l;
        tasks[i].resize(l);
        for(auto &p : tasks[i]) {
            string s; cin >> s;
            p = process(s);
        }
    }
    
    map<long long, int>m;
    int k; cin >> k;
    for(int i = 0; i < k; i++) {
        string s; cin >> s;
        int x; cin >> x;
        m[f(s)] = x;
    }
    
    vector<int>answer;
    while(l_sum > 0) {
        
        bool next = false;
        for(int i = 0; i < n; i++) {
            
            while(!tasks[i].empty() && m.find(tasks[i].back().first) == m.end()) {
                tasks[i].pop_back();
                answer.push_back(i);
                l_sum--;
            }
            
            if(!tasks[i].empty() && m[tasks[i].back().first] == tasks[i].back().second) {
                answer.push_back(i);
                m.erase(m.find(tasks[i].back().first));
                tasks[i].pop_back();
                l_sum--;
                next = true;
                break;
            }
        }
        if(!next && l_sum > 0) {
            cout << "No\n";
            return 0;
        }
    }
    
    cout << "Yes\n";
    reverse(answer.begin(), answer.end());
    for(int x : answer)
        cout << x + 1 << ' ';
    cout << '\n';
    return 0;
}
