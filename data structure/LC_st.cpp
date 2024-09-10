//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;
const double eps = 1e-9;

int T = 1;

class LC_st{
public:
    struct line{
        double k, b;
        double calc(double x){
            return k * x + b;
        }
    };
    vector<line> lib;
    vec f;
    int n;
    int x_size = 39989, y_size = 1e9;
    void init(int cur_n){
        n = cur_n;
        lib.resize(1);
        f.resize(x_size * 4 + bias);
    }
    void add_line(int x0, int x1, int y0, int y1){
        if(x0 == x1){
            lib.push_back((line){0, max((db)y0, (db)y1)});
        }else{
            double k = 1.0 * (y1 - y0) / (x1 - x0);
            double b = y0 - k * x0;
            lib.push_back((line){k, b});
        }
    }
    int cmp(double x, double y){
        if(x - y > eps) return 1;
        if(y - x > eps) return -1;
        return 0;
    }
    void UP(int l, int r, int x, int o){
        int &cur = f[o];
        int mid = (l + r) >> 1;
        int r_mid = cmp(lib[x].calc(mid), lib[cur].calc(mid));
        if(r_mid == 1 || (r_mid == 0 && x < cur)) swap(cur, x);
        int r_l = cmp(lib[x].calc(l), lib[cur].calc(l));
        int r_r = cmp(lib[x].calc(r), lib[cur].calc(r));
        if(r_l == 1 || (r_l == 0 && x < cur)) UP(l, mid, x, o * 2);
        if(r_r == 1 || (r_r == 0 && x < cur)) UP(mid + 1, r, x, o * 2 + 1);

    }
    void update(int l, int r, int s, int t, int x, int o){
        if(l == s && r == t){
            UP(l, r, x, o);
            return;
        }
        int mid = (l + r) >> 1;
        if(t <= mid) update(l, mid, s, t, x, o * 2);
        else if(s > mid) update(mid + 1, r, s, t, x, o * 2 + 1);
        else update(l, mid, s, mid, x, o * 2), update(mid + 1, r, mid + 1, t, x, o * 2 + 1);
    }
    pair<db, int> pmax(pair<db, int> a, pair<db, int> b){
        if(cmp(a.first, b.first) == 1) return a;
        else if(cmp(a.first, b.first) == -1) return b;
        else return make_pair(a.first, min(a.second, b.second));
    }
    pair<db, int> query(int l, int r, int x, int o){
        if(x < l || x > r) return make_pair(-eps, 0);
        pair<db, int> cur = make_pair(lib[f[o]].calc(x), f[o]);
        if(l == r) return cur;
        int mid = (l + r) >> 1;
        return pmax(cur, x <= mid ? query(l, mid, x, o * 2) : query(mid + 1, r, x, o * 2 + 1));
        
    }
};

LC_st LC;

void init(int cur_n){
    LC.init(cur_n);
}

void solve(){
    int n, lastans = 0;
    cin >> n;
    init(n);
    // for(int i = 1, opt, k; i <= n; i++){
    //     cin >> opt;
    //     if(opt == 0){
    //         int x0;
    //         cin >> x0;
    //         x0 = (x0 + lastans -1) % LC.x_size + 1;
    //         cout << (lastans = LC.query(1, LC.x_size, x0, 1).second) << endl;
    //     }else{
    //         int x0, y0, x1, y1;
    //         cin >> x0 >> y0 >> x1 >> y1;
    //         x0 = (x0 + lastans - 1) % LC.x_size + 1;
    //         y0 = (y0 + lastans - 1) % LC.y_size + 1;
    //         x1 = (x1 + lastans - 1) % LC.x_size + 1;
    //         y1 = (y1 + lastans - 1) % LC.y_size + 1;
    //         if(x0 > x1) swap(x0, x1), swap(y0, y1);
    //         LC.add_line(x0, x1, y0, y1);
    //         LC.update(1, LC.x_size, x0, x1, LC.lib.size() - 1, 1);
    //     }
    // }
}

int main(){

//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);    
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // cin >> T;
    while(T--) solve();

    return 0;
}
