#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1ll << 60;

const int MAX_N = 200'007;
vector<int>work_days[MAX_N], holidays[7];
set<pair<long long, long long>>holiday_intervals[7];
vector<int>project_parts[MAX_N];
set<int>pending_assignments[MAX_N];
set<pair<long long, int>>days_and_employees;
long long answer[MAX_N];
bool in[MAX_N];
int n, m, k;

map<string, int>day_id;

long long next_working_day(int employee, long long current_day) {
    current_day++;
    long long result = inf;
    for(int day : work_days[employee]) {
        
        long long my_day = current_day + (day - current_day % 7 + 7) % 7;
        
        auto it = holiday_intervals[day].lower_bound(make_pair(my_day, -1));
        
        if(it == holiday_intervals[day].end()) {
            result = min(result, my_day);
        } else {
            if(it -> second > my_day) {
                result = min(result, my_day);
            } else {
                result = min(result, it -> first + 7);
            }
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    day_id["Monday"] = 0;
    day_id["Tuesday"] = 1;
    day_id["Wednesday"] = 2;
    day_id["Thursday"] = 3;
    day_id["Friday"] = 4;
    day_id["Saturday"] = 5;
    day_id["Sunday"] = 6;
    
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++) {
        int t; cin >> t;
        string day;
        while(t--) {
            cin >> day;
            work_days[i].emplace_back(day_id[day]);
        }
    }
    
    for(int i = 0; i < m; i++) {
        int h; cin >> h; h--;
        holidays[h % 7].push_back(h);
    }
    
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < (int)holidays[i].size(); j++) {
            int k = j + 1;
            while(k < (int)holidays[i].size() && holidays[i][k] - 7 == holidays[i][k - 1])
                k++;
            holiday_intervals[i].insert(make_pair(holidays[i][k - 1], holidays[i][j]));
            j = k - 1;
        }
    }
    
    for(int i = 0; i < k; i++) {
        int p; cin >> p;
        for(int j = 0; j < p; j++) {
            int a; cin >> a; a--;
            project_parts[i].push_back(a);
        }
        reverse(project_parts[i].begin(), project_parts[i].end());
    }
    
    
    for(int i = 0; i < k; i++)
        pending_assignments[project_parts[i].back()].insert(i);
    
    for(int i = 0; i < n; i++) {
        if(!pending_assignments[i].empty()) {
            in[i] = true;
            days_and_employees.insert(make_pair(next_working_day(i, -1), i));
        }
    }
    
    while(!days_and_employees.empty()) {
        long long current_day = days_and_employees.begin() -> first;
        
        vector<int>current_employees;
        while(!days_and_employees.empty() && days_and_employees.begin() -> first == current_day) {
            current_employees.emplace_back(days_and_employees.begin() -> second);
            in[days_and_employees.begin() -> second] = false;
            days_and_employees.erase(days_and_employees.begin());
        }
        
        vector<int>my_projects;
        
        for(int employee : current_employees) {
            int project = *pending_assignments[employee].begin();
            my_projects.push_back(project);
            pending_assignments[employee].erase(pending_assignments[employee].begin());
        }
        
        for(int project : my_projects) {
            project_parts[project].pop_back();
            if(project_parts[project].empty()) {
                answer[project] = current_day + 1;
            } else {
                int next_employee = project_parts[project].back();
                pending_assignments[next_employee].insert(project);
                if(!in[next_employee]) {
                    in[next_employee] = true;
                    days_and_employees.insert(make_pair(next_working_day(next_employee, current_day), next_employee));
                }
                
            }
        }
        
        for(int employee : current_employees) {
            if(!pending_assignments[employee].empty() && !in[employee]) {
                in[employee] = true;
                days_and_employees.insert(make_pair(next_working_day(employee, current_day), employee));
            }
        }
        
    }
    
    for(int i = 0; i < k; i++)
        cout << answer[i] << ' ';
    cout << '\n';
    
    
    return 0;
}
