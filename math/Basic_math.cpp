//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;
const ll mod = 1e9 + 7;
const db eps = 1e-8;

class MATH{
public:
    ll exgcd(ll a,ll b,ll &x,ll &y){
        if(!b){
            x=1,y=0;
            return a;
        }
        ll ret=exgcd(b,a%b,x,y);
        ll t=x;x=y;y=t-a/b*y;
        return ret;
    }

    ll fast_pow(ll bas, ll tims){
        ll ret = 1;
        while(tims){
            if(tims & 1) ret = ret * bas % mod;
            bas = bas * bas % mod;
            tims >>= 1;
        }
        return ret;
    }

    ll inv(ll bas){
        return fast_pow(bas, mod - 2);
    }

    class liner_inv{
    private:
        ll n, mod;
        vector<ll> invs;
    public:
        void init(ll cur_n, ll cur_mod){
            n = cur_n;
            mod = cur_mod;
            invs.resize(n + bias);
            invs[1] = 1;
            for(int i = 2; i <= n; i++) invs[i] = (mod - mod / i) * invs[mod % i] % mod;
        }
        ll get_inv(ll x){
            return invs[x];
        }
    };

    class eluer_shieves{
    private:
        int n, cnt;
        vector<int> prim, vis;
    public:
        void init(int cur_n){
            n = cur_n;
            cnt = 0;
            prim.resize(n + bias);
            vis.resize(n + bias);
        }
        void shieves(){
            for(int i = 2; i <= n; i++){
                if(!vis[i]) prim[++cnt] = i;
                for(int j = 1; j <= cnt && prim[j] * i < n; j++){
                    vis[prim[j] * i] = 1;
                    if(i % prim[j] == 0) break;
                }
            }
        }
    };

    class Matrix{
    public:
        struct Mat{
            int n, m;
            vector<vector<ll>> mat;
            Mat(int n = 0, int m = 0):n(n), m(m){
                mat.resize(n);
                for(int i = 0; i < n; i++) mat[i].resize(m);
            }
            Mat operator *(const Mat &x)const{
                Mat ret;
                ret.n = n, ret.m = x.m;
                ret.mat.resize(n);
                for(int i = 0; i < n; i++) ret.mat[i].resize(x.m);
                for(int i = 0; i < n; i++){
                    for(int j = 0; j < x.m; j++){
                        for(int k = 0; k < m; k++){
                            ret.mat[i][j] += mat[i][k] * x.mat[k][j];
                            ret.mat[i][j] %= mod;
                        }
                    }
                }
                return ret;
            }
        };
        Mat fast_pow(Mat a, ll k){
            Mat ret;
            ret.n = a.n, ret.m = a.n;
            ret.mat.resize(a.n);
            for(int i = 0; i < a.n; i++) ret.mat[i].resize(a.n);
            for(int i = 0; i < a.n; i++) ret.mat[i][i] = 1;
            while(k){
                if(k & 1) ret = ret * a;
                a = a * a;
                k >>= 1;
            }
            return ret;
        }
    };

    class Gaussian_elimination{
    public:
        vector<vector<db> > a;
        vector<db> b, t, x;
        int n;
        void init(int cur_n){
            n = cur_n;
            a.resize(n + bias);
            for(int i = 0; i <= n; i++) a[i].resize(n + bias);
            b.resize(n + bias);
            t.resize(n + bias);
            x.resize(n + bias);
        }
        void solve(){
            for(int i = 1; i <= n; i++){
                for(int j = i + 1; j <= n; j++) t[j] = a[j][i] / a[i][i];
                for(int j = i + 1; j <= n; j++){
                    for(int k = 1; k <= n; k++) a[j][k] -= t[j] * a[i][k];
                    b[j] -= t[j] * b[i];
                }
            }
            for(int i = n; i >= 1; i--){
                if(fabs(a[i][i]) < eps){
                    cout << "No Solution";
                    return;
                }else{
                    x[i] = b[i] / a[i][i];
                    for(int j = i - 1; j >= 1; j--){
                        b[j] -= a[j][i] * x[i];
                        a[j][i] = 0;
                    }
                }
            }
        }
    };
};

