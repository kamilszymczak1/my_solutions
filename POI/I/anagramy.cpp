#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<pair<vector<int>, string>>words;
    for(int i = 0; i < n; i++) {
        vector<int>char_count(26);
        string s; cin >> s;
        for(char c : s)
            char_count[c - 'a']++;
        words.emplace_back(char_count, s);
    }
    sort(words.begin(), words.end());
    
    vector<vector<string>>classes;
    
    for(int i = 0; i < n; i++) {
        int j = i;
        classes.emplace_back();
        while(j < n && words[i].first == words[j].first) {
            classes.back().emplace_back(words[j].second);
            j++;
        }
        i = j - 1;
    }
    
    for(vector<string>&v : classes) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }
    sort(classes.begin(), classes.end());
    
    for(vector<string>&v : classes) {
        for(string s : v) {
            cout << s << ' ';
        }
        cout << '\n';
    }
    
    return 0;
}

/*


10
liszka
tuba
tuba
klisza
kretes
anakonda
sekret
szalik
buta
tabu


*/
