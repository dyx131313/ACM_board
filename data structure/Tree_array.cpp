//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

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