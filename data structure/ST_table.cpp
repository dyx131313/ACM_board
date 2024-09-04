//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class ST_table{
private:
    int n;
    vector<vector<int> > st;
    vector<int> log_2;
public:
    void init(int cur_n){
        n = cur_n;
        log_2.resize(n + bias);
        log_2[0] = 0;
        for(int i = 2; i <= n; i++)
            log_2[i] = log_2[i / 2] + 1;
        st.resize(log_2[n] + 1, vector<int>(n + bias));
    }
    int query(int x, int y){
        return max(st[log_2[y - x]][y], st[log_2[y - x]][x + (1 << (log_2[y - x])) - 1]);
    }
};