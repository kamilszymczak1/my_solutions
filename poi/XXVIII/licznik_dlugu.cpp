#include <iostream>
#include <set>

using namespace std;

const int MAX_N = 100007, zero = 0, nine = 1;
const int num[2] = {0, 9};

struct Interval {
    int a, b;
    Interval(int _a, int _b) : a(_a), b(_b) {}
};

struct Comp {bool operator() (Interval x, Interval y) const {return x.a < y.a;}};

int number[2][MAX_N], sum[MAX_N];
int n, z;

set<Interval, Comp>sets[2];

int Query(int i);

bool InInterval(int i, set<Interval, Comp>&s);

void ReadData();
void Update(int j, int i, int newVal);
void RemoveElement(int x, set<Interval, Comp>&s);
void AddInterval(Interval interval, set<Interval, Comp>&s);

int main() {
    ios_base::sync_with_stdio(0);
    
    ReadData();
    
    char t;
    int a, b;
    for(int i = 0; i < z; i++) {
        cin >> t;
        if(t == 'S') {
            cin >> a;
            cout << Query(a) << "\n";
        } else {
            cin >> a >> b;
            Update(t == 'W' ? 0 : 1, a - 1, b);
        }
    }
    
    return 0;
}

void RemoveElement(int x, set<Interval, Comp>&s) {
    auto it = s.upper_bound(Interval(x, x));
    it--;
    Interval left = Interval(it -> a, x - 1);
    Interval right = Interval(x + 1, it -> b);
    s.erase(it);
    if(left.a <= left.b)
        s.insert(left); 
    if(right.a <= right.b)
        s.insert(right);
}

void AddInterval(Interval interval, set<Interval, Comp>&s) {
    if(s.empty()) {
        s.insert(interval);
        return;
    }
    
    auto right = s.lower_bound(interval), left = s.end();
    
    if(right != s.begin())
        left = right, left--;
    
    if(right != s.end() && interval.b + 1 >= right -> a) {
        interval = Interval(min(interval.a, right -> a), max(interval.b, right -> b));
        s.erase(right);
    }
    
    if(left != s.end() && left -> b + 1 >= interval.a) {
        interval = Interval(min(interval.a, left -> a), max(interval.b, left -> b));
        s.erase(left);
    }
    
    s.insert(interval);
}

int Query(int i) {
    if(InInterval(i - 1, sets[nine]))
        return 9;
    if(InInterval(i - 1, sets[zero]))
        return 0;
    return sum[i - 1];
}

void Update(int j, int i, int newVal) {
    if(number[j][i] == newVal)
        return;
    
    int prevVal = number[j][i];
    number[j][i] = newVal;
    
    for(int k = 0; k < 2; k++)
        if(InInterval(i, sets[k]))
            sum[i] = num[k], RemoveElement(i, sets[k]);
        
    
    sum[i] += newVal - prevVal;
    
    int a = zero, b = nine;
    if(sum[i] < 0)
        swap(a, b);
    
    if(sum[i] < 0 || sum[i] >= 10) {
        auto nextRight = sets[b].upper_bound(Interval(i, i));
        int right = i + 1;
        if(nextRight != sets[b].end() && nextRight -> a == right) {
            right = nextRight -> b + 1;
            sets[b].erase(nextRight);
            sets[a].insert(Interval(i + 1, right - 1));
        }
        if(InInterval(right, sets[a]))
            RemoveElement(right, sets[a]);
        sum[right] += sum[i] > 0 ? 1 : -1;
        if(sum[right] == num[b])
            AddInterval(Interval(right, right), sets[b]);
    }
    
    sum[i] = (sum[i] + 10) % 10;
    
    for(int k = 0; k < 2; k++)
        if(sum[i] == num[k])
            AddInterval(Interval(i, i), sets[k]);
}

bool InInterval(int i, set<Interval, Comp>&s) {
    if(s.empty())
        return false;
    auto it = s.lower_bound(Interval(i, i));
    if(it != s.end() && it -> a <= i && i <= it -> b)
        return true;
    if(it != s.begin()) {
        it--;
        if(it -> a <= i && i <= it -> b)
            return true;
    }
    return false;
}

void ReadData() {
    string s[2];
    cin >> n >> z >> s[0] >> s[1];
    
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < n - 1; j++)
            number[i][j] = s[i][s[i].size() - j - 1] - '0';
    
    for(int i = 0; i < n; i++) {
        if(sum[i] + number[0][i] + number[1][i] >= 10)
            sum[i + 1]++;
        sum[i] = (sum[i] + number[0][i] + number[1][i]) % 10;
    }
    
    for(int i = 0; i < 2; i++)
        for(int j = 0; j < n; j++) {
            int k = j;
            while(k < n && sum[k] == num[i])
                k++;
            if(k > j) {
                sets[i].insert(Interval(j, k - 1));
                j = k - 1;
            }
        }
}
