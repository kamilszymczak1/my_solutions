#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
#include <set>

using namespace std;

struct Group {
    vector<pair<int, int>>students;
    long double average;
    int size() {
        return students.size();
    }
};

bool cmp(Group &A, Group &B) {
    return A.average < B.average;
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<int>a(n);
    for(int &x : a)
        cin >> x;
    sort(a.begin(), a.end());
    
    int totalStudents = 0;
    vector<Group>groups(m);
    for(Group &g : groups) {
        int k; cin >> k;
        g.average = 0;
        g.students.resize(k);
        for(auto &[age, id] : g.students) {
            cin >> age; g.average += age;
            id = totalStudents++;
        }
        g.average /= k;
    }
    
    sort(groups.begin(), groups.end(), cmp);
    
    vector<int>matching(m, -1), nextFixed(m, -1);
    vector<bool>canBeShifted(m, false), takenTeacher(n + 1, false);
    set<int>freeTeachers;
    
    matching[0] = lower_bound(a.begin(), a.end(), ceil(groups[0].average)) - a.begin();
    takenTeacher[matching[0]] = true;
    int unmatchedCount = matching[0] == n;
    for(int i = 1; i < m; i++) {
        matching[i] = lower_bound(a.begin(), a.end(), ceil(groups[i].average)) - a.begin();
        if(matching[i - 1] < n) {
            canBeShifted[i] = matching[i] <= matching[i - 1];
            matching[i] = max(matching[i], matching[i - 1] + 1);
        }
        unmatchedCount += matching[i] == n;
        takenTeacher[matching[i]] = true;
    }
    
    for(int i = 0; i < n; i++) {
        if(!takenTeacher[i]) {
            freeTeachers.insert(i);
        }
    }
    
    nextFixed[m - 1] = m;
    for(int i = m - 2; i >= 0; i--) {
        if(!canBeShifted[i + 1]) {
            nextFixed[i] = i + 1;
        } else {
            nextFixed[i] = nextFixed[i + 1];
        }
    }
    
    vector<bool>ans(totalStudents, false);
    
    if(unmatchedCount == 0) {
        
        for(int i = 0; i < m; i++) {
            for(auto [age, id] : groups[i].students) {
                long double newAverage = ((groups[i].average * groups[i].size()) - age) / (groups[i].size() - 1);
                freeTeachers.insert(matching[nextFixed[i] - 1]);
                ans[id] = a[*freeTeachers.rbegin()] >= ceil(newAverage);
                freeTeachers.erase(matching[nextFixed[i] - 1]);
            }
            
        }
        
    } else if(unmatchedCount == 1) {
        for(int i = 0; i < m; i++) {
            if(nextFixed[i] != m)
                continue;
            for(auto [age, id] : groups[i].students) {
                long double newAverage = ((groups[i].average * groups[i].size()) - age) / (groups[i].size() - 1);
                ans[id] = a[*freeTeachers.rbegin()] >= ceil(newAverage);
            }
            
        }
    }
    
    for(bool b : ans)
        cout << b;
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t; cin >> t;
    while(t--)
        TestCase();
    
    return 0;
}
