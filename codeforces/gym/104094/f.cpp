#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

struct query {
    int l, r, lo, hi, id;
    query() {}
    query(int _l, int _r, int _lo, int _hi, int _id) : l(_l), r(_r), lo(_lo), hi(_hi), id(_id) {}
    int mid() { return (lo + hi) / 2; }
};

bool operator< (query a, query b) {
    return a.mid() < b.mid();
}

struct solver {
    vector<bool>status;
    set<int>ones, double_ones, odd_zeroes, even_zeroes;
    solver(int n) {
        status.resize(n, false);
        if(n % 2 == 0) {
            even_zeroes.insert(0);
        } else {
            odd_zeroes.insert(0);
        }
        ones.insert(-1);
        ones.insert(n);
    }
    
    void toggle(int x) {
        cout << "toggle " << x << "\n" << flush;
        status[x] = true;
        ones.insert(x);
        if(x != 0 && status[x - 1] == true)
            double_ones.insert(x - 1);
        if(x + 1 != (int)status.size() && status[x + 1] == true)
            double_ones.insert(x);
        
        if((x == 0 || status[x - 1] == true) && (x + 1 == (int)status.size() || status[x + 1] == true)) {
            odd_zeroes.erase(odd_zeroes.find(x));
        }
        
        if((x == 0 || status[x - 1] == true) && x + 1 != (int)status.size() && status[x + 1] == false) {
            if(odd_zeroes.find(x) != odd_zeroes.end()) {
                odd_zeroes.erase(odd_zeroes.find(x));
                even_zeroes.insert(x + 1);
            } else {
                even_zeroes.erase(even_zeroes.find(x));
                odd_zeroes.insert(x + 1);
            }
        }
        
        if((x + 1 == (int)status.size() || status[x + 1] == true) && x != 0 && status[x - 1] == false) {
            int left_one = *(--ones.find(x));
            if(odd_zeroes.find(left_one + 1) != odd_zeroes.end()) {
                odd_zeroes.erase(odd_zeroes.find(left_one + 1));
                even_zeroes.insert(left_one + 1);
            } else {
                even_zeroes.erase(even_zeroes.find(left_one + 1));
                odd_zeroes.insert(left_one + 1);
            }
        }
        
        if(x != 0 && status[x - 1] == false && x + 1 != (int)status.size() && status[x + 1] == false) {
            int left_one = *(--ones.find(x));
            int parity = odd_zeroes.find(left_one + 1) == odd_zeroes.end() ? 0 : 1;
            
            cout << "left_one = " << left_one << '\n' << flush;
            cout << "parity = " << parity << '\n' << flush;
            
            if(parity == 1) {
                odd_zeroes.erase(odd_zeroes.find(left_one + 1));
            } else {
                even_zeroes.erase(even_zeroes.find(left_one + 1));
            }
            
            if((x - 1 - left_one) % 2 == 0) {
                even_zeroes.insert(left_one + 1);
            } else {
                odd_zeroes.insert(left_one + 1);
            }
            
            if((parity + 1 - (x - 1 - left_one) % 2) % 2 == 0) {
                even_zeroes.insert(x + 1);
            } else {
                odd_zeroes.insert(x + 1);
            }
        }
        
        
        cout << "toggle end\n" << flush;
    }
    
    bool query(int l, int r) {
        cout << "query\n" << flush;
        auto l_it = ones.lower_bound(l);
        if(l_it == ones.end() || *l_it > r)
            return false;
        int ll = *l_it;
        int rr = *(--ones.upper_bound(r));
        
        auto d_o = double_ones.lower_bound(ll);
        if(d_o != double_ones.end() && *d_o < r)
            return true;
        
        auto left_double_zero_it = even_zeroes.lower_bound(ll);
        
        if(left_double_zero_it == even_zeroes.end() || *left_double_zero_it >= rr) {
            //there is no double zero
            if(l == ll && r == rr && status[l] == true)
                return true;
            return false;
        }
        auto right_double_zero_it = --even_zeroes.upper_bound(rr);
        
        if(left_double_zero_it == right_double_zero_it)
            return false;
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    
    int n; cin >> n;
    vector<pair<int, int>>v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    
    sort(v.begin(), v.end(), greater<pair<int, int>>());
    
    int q; cin >> q;
    vector<query>queries;
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries.emplace_back(l - 1, r - 1, 0, n - 1, i);
    }
    
    
    bool searching;
    
    int it = 0;
    do {
        it++;
        cout << "next iteration\n" << flush;
        searching = false;
        
        sort(queries.begin(), queries.end());
        
        solver my_solver(n);
        
        int v_ind = 0;
        for(query &q : queries) {
            
            cout << "mid = " << q.mid() << '\n';
            
            while(v_ind < n && v[v_ind].first >= q.mid()) {
                my_solver.toggle(v[v_ind].second);
                v_ind++;
            }
            
            if(my_solver.query(q.l, q.r)) {
                cout << "true\n";
                q.hi = q.mid();
            } else {
                cout << "false\n";
                q.lo = q.mid() + 1;
            }
            
            if(q.lo != q.hi)
                searching = true;
        }
        
        cout << "bounds\n";
        for(query q : queries) {
            cout << q.id + 1 << ": " << q.lo << ' ' << q.hi << '\n' << flush;
        }
        
    } while(searching && it < 3);
    
    vector<int>answer(q);
    for(query q : queries)
        answer[q.id] = q.lo;
    
    for(int x : answer)
        cout << x << '\n';
    
    return 0;
}
