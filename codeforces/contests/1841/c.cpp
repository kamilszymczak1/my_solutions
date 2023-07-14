#include <iostream>
#include <vector>
#include <map>

using namespace std;

void test_case() {
    string s; cin >> s;
    map<char, int>m;
    m['A'] = 0;
    m['B'] = 1;
    m['C'] = 2;
    m['D'] = 3;
    m['E'] = 4;
    int n = s.size();
    vector<int>v(n);
    for(int i = 0; i < n; i++)
        v[i] = m[s[i]];
    
    vector<int>val(5);
    val[0] = 1;
    val[1] = 10;
    val[2] = 100;
    val[3] = 1000;
    val[4] = 10000;
    
    vector<int>cnt(5);
    vector<pair<int, int>>right;
    right.emplace_back(5, n);
    
    vector<int>sign(n);
    
    vector<vector<int>>positive_cnt_left(n, vector<int>(5));
    vector<vector<int>>negative_cnt_left(n, vector<int>(5));
    
    long long total_sum = 0;
    
    for(int i = n - 1; i >= 0; i--) {
        while(right.back().first <= v[i])
            right.pop_back();
        right.emplace_back(v[i], i);
        int cnt_higher_sum = 0;
        for(int j = v[i] + 1; j < 5; j++)
            cnt_higher_sum += cnt[j];
        if(cnt_higher_sum == 1) {
            negative_cnt_left[right[1].second][v[i]]++;
        }
        sign[i] = cnt_higher_sum == 0 ? 1 : -1;
        cnt[v[i]]++;
        total_sum += val[v[i]] * sign[i];
    }
    
    long long result = total_sum;
    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < 5; j++)
            positive_cnt_left[i][j] = positive_cnt_left[i - 1][j];
        if(sign[i - 1] == 1)
            positive_cnt_left[i][v[i - 1]]++;
    }
    
    fill(cnt.begin(), cnt.end(), 0);
    
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j < v[i]; j++) {
            long long local_sum = total_sum;
            local_sum -= sign[i] * val[v[i]];
            
            int cnt_higher_sum = 0;
            for(int k = j + 1; k < 5; k++)
                cnt_higher_sum += cnt[k];
            if(cnt_higher_sum == 0) {
                local_sum += val[j];
            } else {
                local_sum -= val[j];
            }
            
            for(int k = j; k < 5; k++) {
                local_sum += 2 * negative_cnt_left[i][k] * val[k];
            }
            
            result = max(result, local_sum);
        }
        
        for(int j = v[i] + 1; j < 5; j++) {
            long long local_sum = total_sum;
            local_sum -= sign[i] * val[v[i]];
            
            int cnt_higher_sum = 0;
            for(int k = j + 1; k < 5; k++)
                cnt_higher_sum += cnt[k];
            if(cnt_higher_sum == 0) {
                local_sum += val[j];
            } else {
                local_sum -= val[j];
            }
            
            for(int k = 0; k < j; k++) {
                local_sum -= 2 * positive_cnt_left[i][k] * val[k];
            }
            result = max(result, local_sum);
        }
        
        cnt[v[i]]++;
    }
    
    cout << result << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--)
        test_case();
    return 0;
}
