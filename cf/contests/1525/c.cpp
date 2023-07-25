#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

const int LEFT = 1, RIGHT = 2;

struct Robot {
    int x, ind, dir;
    Robot(int _x, int _ind, int _dir) : x(_x), ind(_ind), dir(_dir) {}
};

bool cmp(Robot &a, Robot &b) {
    return a.x < b.x;
}

void Solve(vector<Robot>&robots, int m, vector<int>&ans) {
    vector<Robot>leftEmptyRobots, rightEmptyRobots;
    stack<Robot>lastGoingToRight;
    sort(robots.begin(), robots.end(), cmp);
    for(auto r : robots) {
        if(r.dir == LEFT) {
            if(lastGoingToRight.empty()) {
                leftEmptyRobots.push_back(r);
            } else {
                auto R = lastGoingToRight.top();
                lastGoingToRight.pop();
                int meetTime = (r.x - R.x) / 2;
                ans[R.ind] = meetTime;
                ans[r.ind] = meetTime;
            }
        } else {
            lastGoingToRight.push(r);
        }
    }
    
    while(!lastGoingToRight.empty()) {
        rightEmptyRobots.push_back(lastGoingToRight.top());
        lastGoingToRight.pop();
    }
    
    
    for(int i = 0; 2 * i + 1 < leftEmptyRobots.size(); i++) {
        int meetTime = (leftEmptyRobots[i * 2].x + leftEmptyRobots[i * 2 + 1].x) / 2;
        ans[leftEmptyRobots[i * 2].ind] = meetTime;
        ans[leftEmptyRobots[i * 2 + 1].ind] = meetTime;
    }  
    
    for(int i = 0; 2 * i + 1 < rightEmptyRobots.size(); i++) {
        int meetTime = (m - rightEmptyRobots[i * 2].x + m - rightEmptyRobots[i * 2 + 1].x) / 2;
        ans[rightEmptyRobots[i * 2].ind] = meetTime;
        ans[rightEmptyRobots[i * 2 + 1].ind] = meetTime;
    }  
    
    Robot leftRobot = ((int)leftEmptyRobots.size() & 1) ? leftEmptyRobots.back() : Robot(0, -1, 0);
    Robot rightRobot = ((int)rightEmptyRobots.size() & 1) ? rightEmptyRobots.back() : Robot(0, -1, 0);
    
    if(leftRobot.ind >= 0 && rightRobot.ind >= 0) {
        int meetTime = m + (leftRobot.x - rightRobot.x) / 2;
        ans[leftRobot.ind] = meetTime;
        ans[rightRobot.ind]  = meetTime;
    }
    
    
}

void TestCase() {
    int n, m; cin >> n >> m;
    vector<int>ans(n, -1), initPos(n), dir(n);
    vector<Robot>oddRobots, evenRobots;
    for(auto &x : initPos)
        cin >> x;
    for(auto &d : dir) {
        char c; cin >> c;
        d = c == 'L' ? LEFT : RIGHT;
    }
    
    for(int i = 0; i < n; i++) {
        if(initPos[i] & 1)
            oddRobots.push_back(Robot(initPos[i], i, dir[i]));
        else
            evenRobots.push_back(Robot(initPos[i], i, dir[i]));
    }
    
    Solve(oddRobots, m, ans);
    Solve(evenRobots, m, ans);
    for(auto x : ans)
        cout << x << ' ';
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    int t;
    cin >> t;
    while(t--) {
        TestCase();
    }
    return 0;
}
