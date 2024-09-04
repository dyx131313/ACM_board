//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class CDQ{
private:
    int n;
    struct info{
        int x, y, z, id;
    };
    vector<info> lib;
    vector<int> num, b, ans, f;
    class Tree_array{
    private:
        vector<ll> f;
        ll n;
    public:
        void init(int cur_n){
            n = cur_n;
            f.resize(n + bias);
            fill(f.begin(), f.end(), 0);
        }
        int lowbit(int x){return x & -x;}
        void add(int x,ll k){
            for(int i = x; i <= n; i += lowbit(i)) 
                f[i] += k;
        }
        ll query(int x){
            ll ret = 0;
            for(int i = x; i; i -= lowbit(i)) ret += f[i];
            return ret;
        }
    };
    tree_array t_a;
public:
    void init(int cur_n){
        n = cur_n;
        t_a.init(n);
        lib.resize(n + bias);
        num.resize(n + bias); b.resize(n + bias); ans.resize(n + bias); f.resize(n + bias);
    }
    static bool cmp1(const info &a, const info &b){
        if(a.x != b.x) return a.x < b.x;
	    if(a.y != b.y) return a.y < b.y;
	    return a.z < b.z;
    }//range by x, y, z
    static bool cmp2(const info &a, const info &b){
        if(a.y != b.y) return a.y < b.y;
        if(a.z != b.z) return a.z < b.z;
        return a.x < b.x;
    }//range by y, z, x
    void cdq(int l, int r){
        if(l == r){
            return;
        }
        int mid = (l + r) >> 1;
        cdq(l, mid); cdq(mid + 1, r);
        sort(lib.begin() + l, lib.begin() + r + 1, cmp2);
        for(int i=l; i <= r; i++){
            if(lib[i].x <= mid) t_a.add(lib[i].z, 1);
            else b[lib[i].id] += t_a.query(lib[i].z); 
        } 
        for(int i=l; i <= r; i++){
            if(lib[i].x <= mid) t_a.add(lib[i].z, -1);
        }
    }
};