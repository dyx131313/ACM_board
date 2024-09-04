//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class Segment_tree{
private:
    int n;
    ll mod;
    vector<ll> sum;
    vector<ll> lazytag_add;
    vector<ll> lazytag_mul;
    vector<ll> s;
public:
    void combine_inf(int o){
        sum[o] = (sum[o * 2] + sum[o * 2 + 1]) % mod;
    }
    void tree_build(int l, int r, int o){
        lazytag_mul[o] = 1;
        if(l == r){
            sum[o] = s[l];
            return;
        }
        int mid= (l + r) >> 1;
        tree_build(l, mid, o * 2);
        tree_build(mid + 1, r, o * 2 + 1);
        combine_inf(o);
    }
    void init(int cur_n){
        n = cur_n;
        sum.resize(n * 4 + bias);
        lazytag_add.resize(n * 4 + bias);
        lazytag_mul.resize(n * 4 + bias);
        s.resize(n + bias);
    }
    void markdown(int l, int r, int o){
        int mid = (l + r) >> 1;
        sum[o * 2] = (sum[o * 2] * lazytag_mul[o] % mod + lazytag_add[o] * (mid - l + 1) % mod) % mod;
        sum[o * 2 + 1] = (sum[o * 2 + 1] * lazytag_mul[o] % mod + lazytag_add[o] * (r - mid) % mod) % mod;
        lazytag_add[o * 2] = (lazytag_add[o * 2] * lazytag_mul[o] + lazytag_add[o]) % mod;
        lazytag_add[o * 2 + 1] = (lazytag_add[o * 2 + 1] * lazytag_mul[o] + lazytag_add[o]) % mod;
        lazytag_mul[o * 2] = lazytag_mul[o * 2] * lazytag_mul[o] % mod;
        lazytag_mul[o * 2 + 1] = lazytag_mul[o * 2 + 1] * lazytag_mul[o] % mod;
        lazytag_add[o] = 0, lazytag_mul[o] = 1;
    }
    void section_mul(int l, int r, int s, int t, ll x, int o){
        if(l == s && r == t){
            sum[o] = sum[o] * x % mod;
            lazytag_add[o] = lazytag_add[o] * x % mod;
            lazytag_mul[o] = lazytag_mul[o] * x % mod;
            return;
        }
        if(lazytag_add[o] || lazytag_mul[o] != 1) markdown(l, r, o);
        int mid = (l + r) >> 1;
        if(t <= mid) section_mul(l, mid, s, t, x, o * 2);
        else if(s > mid) section_mul(mid + 1, r, s, t, x, o * 2 + 1);
        else section_mul(l, mid, s, mid, x, o * 2), section_mul(mid + 1, r, mid + 1, t, x, o * 2 + 1);
        combine_inf(o);
    }
    void section_add(int l, int r, int s, int t, ll x, int o){
        if(l == s && r == t){
            sum[o] = (sum[o] + x * (r - l + 1)) % mod;
            lazytag_add[o] = (lazytag_add[o] + x) % mod;
            return;
        }
        if(lazytag_add[o] || lazytag_mul[o] != 1) markdown(l, r, o);
        int mid = (l + r) >> 1;
        if(t <= mid) section_add(l, mid, s, t, x, o * 2);
        else if(s > mid) section_add(mid + 1, r, s, t, x, o * 2 + 1);
        else section_add(l, mid, s, mid, x, o * 2), section_add(mid + 1, r, mid + 1, t, x, o * 2 + 1);
        combine_inf(o);
    }
    ll section_sum_query(int l, int r, int s, int t, int o){
        if(l == s && r == t) return sum[o];
        if(lazytag_add[o] || lazytag_mul[o] != 1) markdown(l, r, o);
        int mid = (l + r) >> 1;
        if(t <= mid) return section_sum_query(l, mid, s, t, o * 2);
        else if(s > mid) return section_sum_query(mid + 1, r, s, t, o * 2 + 1);
        else return (section_sum_query(l, mid, s, mid, o * 2) + section_sum_query(mid + 1, r, mid + 1, t, o * 2 + 1)) % mod;
    }
};