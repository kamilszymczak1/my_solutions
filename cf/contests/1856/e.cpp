#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
    
using namespace std;
    
bitset<500'001>lb;
bitset<50001>mb;
bitset<501>sb;
    
int get(vector<int>&v) {
    int sum = 0;
    for(int &x : v)
        sum += x;
    
    sort(v.begin(), v.end());
    
    vector<int>new_v;
    
    int n = v.size();
    for(int i = 0; i < n; i++) {
        int j = i;
        while(j < n && v[i] == v[j])
            j++;
        long long count = j - i;
        
        long long my_pow = 1;
        while(my_pow <= count) {
            new_v.push_back(my_pow * v[i]);
            count -= my_pow;
            my_pow *= 2;
        }
        
        if(count != 0)
            new_v.push_back(count * v[i]);
        
        i = j - 1;
    }
    
    swap(v, new_v);
    
    int bag_size = sum / 2;
    if(bag_size <= 500) {
        sb.reset();
        sb[0] = true;
        for(int x : v)
            sb = sb | sb << x;
        int result = 0;
        for(int i = 0; i <= bag_size; i++) {
            if(sb[i]) {
                result = i;
            }
        }
        return result;
    } else if(bag_size <= 50000) {
        mb.reset();
        mb[0] = true;
        for(int x : v)
            mb = mb | mb << x;
        int result = 0;
        for(int i = 0; i <= bag_size; i++) {
            if(mb[i]) {
                result = i;
            }
        }
        return result;
    } else {
        lb.reset();
        lb[0] = true;
        for(int x : v)
            lb = lb | lb << x;
        int result = 0;
        for(int i = 0; i <= bag_size; i++) {
            if(lb[i]) {
                result = i;
            }
        }
        return result;
    }
}
    
void test_case() {
    int n; cin >> n;
    vector<vector<int>>children(n);
    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        children[p - 1].push_back(i);
    }
    
    vector<long long>subtree(n, 1);
    for(int i = n - 1; i >= 0; i--) {
        for(int x : children[i]) {
            subtree[i] += subtree[x];
        }
    }
    long long result = 0;
    for(int i = 0; i < n; i++) {
        long long max_child = 0;
        for(int x : children[i]) {
            max_child = max(max_child, subtree[x]);
        }
        
        if(max_child * 2 >= subtree[i] - 1) {
            result += max_child * (subtree[i] - 1 - max_child);
        } else {
            vector<int>v;
            for(int x : children[i])
                v.emplace_back(subtree[x]);
            
            long long opt_size = get(v);
            result += opt_size * (subtree[i] - 1 - opt_size);
        }
    }
    
    cout << result << '\n';
}
    
int main() {
    ios_base::sync_with_stdio(0);
    
    int t = 1;
    while(t--)
        test_case();
    
    return 0;
}
