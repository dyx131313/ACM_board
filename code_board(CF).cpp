//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

int T;

class SegmentTree {
private:
    vector<long long> tree, lazy;
    int n;

    void build(const vector<long long>& arr, int l, int r, int node) {
        if (l == r) {
            tree[node] = arr[l];
        } else {
            int mid = (l + r) / 2;
            build(arr, l, mid, 2 * node + 1);
            build(arr, mid + 1, r, 2 * node + 2);
            tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
        }
    }

    void updateRange(int l, int r, int ql, int qr, long long val, int node) {
        if (lazy[node] != -1) {
            tree[node] = (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[2 * node + 1] = lazy[node];
                lazy[2 * node + 2] = lazy[node];
            }
            lazy[node] = -1;
        }

        if (l > r || l > qr || r < ql) return;

        if (l >= ql && r <= qr) {
            tree[node] = (r - l + 1) * val;
            if (l != r) {
                lazy[2 * node + 1] = val;
                lazy[2 * node + 2] = val;
            }
            return;
        }

        int mid = (l + r) / 2;
        updateRange(l, mid, ql, qr, val, 2 * node + 1);
        updateRange(mid + 1, r, ql, qr, val, 2 * node + 2);
        tree[node] = tree[2 * node + 1] + tree[2 * node + 2];
    }

    long long queryRange(int l, int r, int ql, int qr, int node) {
        if (lazy[node] != -1) {
            tree[node] = (r - l + 1) * lazy[node];
            if (l != r) {
                lazy[2 * node + 1] = lazy[node];
                lazy[2 * node + 2] = lazy[node];
            }
            lazy[node] = -1;
        }

        if (l > r || l > qr || r < ql) return 0;

        if (l >= ql && r <= qr) return tree[node];

        int mid = (l + r) / 2;
        return queryRange(l, mid, ql, qr, 2 * node + 1) + queryRange(mid + 1, r, ql, qr, 2 * node + 2);
    }

public:
    SegmentTree(const vector<long long>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, -1);
        build(arr, 0, n - 1, 0);
    }

    void updateRange(int ql, int qr, long long val) {
        updateRange(0, n - 1, ql, qr, val, 0);
    }

    long long queryRange(int ql, int qr) {
        return queryRange(0, n - 1, ql, qr, 0);
    }
};


int n;

void solve(){
    cin >> n;
    vector<ll> arr(n);
    for(int i = 0; i < n; i++) cin >> arr[i];
    SegmentTree tree(arr);

    ll minn = arr[0];

    for(int i = 1 ; i < n; i++){
        if(tree.queryRange(i - 1, i - 1) > tree.queryRange(i, i)){
            int L = 0, R = i - 1;
            while(L + 1 < R){
                int mid = (L + R) >> 1;
                ll avg = (tree.queryRange(mid, i))/ (i - mid + 1);
                bool is_ok = (avg > (mid == 0)? 0: tree.queryRange(mid - 1, mid - 1));
                if(is_ok) L = mid + 1;
                else R = mid;
            }
            ll sum = tree.queryRange(L, i);
            ll avg = sum / (i - L + 1);
            int is_left = static_cast<int>(sum % (i - L + 1));
            printf("i: %d L: %d avg: %lld is_left: %d sum: %lld\n", i, L, avg, is_left, sum);
            tree.updateRange(L, i - is_left, avg);
            if(is_left) tree.updateRange(i - is_left + 1, i, avg + 1);
        }
    }
    
    cout << tree.queryRange(n - 1, n - 1) - tree.queryRange(0, 0)<< endl;
}

int main(){

//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);    
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> T;
    while(T--) solve();

    return 0;
}
/*
1
4
4 2 3 1

*/