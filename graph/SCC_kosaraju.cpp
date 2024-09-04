//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class Kosaraju{
private:
    class Chain_forward{
    public:
        struct edge{
            int to, nex, weight;
        };
        vector<edge> e;
        vector<int> head;
        int n, m, cnt;
        void init(int cur_n, int cur_m){
            n = cur_n;
            m = cur_m;
            cnt = 0;
            head.resize(n + bias);
            fill(head.begin(), head.end(), 0);
            e.resize(m + bias);
        }
        void add_edge(int a, int b, int c){
            e[++cnt].to = b;
            e[cnt].nex = head[a];
            e[cnt].weight = c;
            head[a] = cnt;
        }
    };
    vector<int> vis, SCC_num;
    Chain_forward G, inv_G;
    int n, m, SCC_cnt;
    vec inv_seq;
public:
    void init(int cur_n, int cur_m){
        n = cur_n;
        m = cur_m;
        vis.resize(n + bias);
        SCC_num.resize(n + bias);
        G.init(n, m);
        inv_G.init(n, m);
        SCC_cnt = 0;
    }
    void add_edge(int a, int b, int c){
        G.add_edge(a, b, c);
        inv_G.add_edge(b, a, c);
    }
    void post_order_dfs(int u){
        vis[u] = 1;
        for(int i = G.head[u]; i; i = G.e[i].nex){
            int v = G.e[i].to;
            if(!vis[v]) post_order_dfs(v);
        }
        inv_seq.push_back(u);
    }
    void inv_dfs(int u, int k){
        SCC_num[u] = k;
        for(int i = inv_G.head[u]; i; i = inv_G.e[i].nex){
            int v = inv_G.e[i].to;
            if(!SCC_num[v]) inv_dfs(v, k);
        }
    }
    void kosaraju(){
        for(int i = 1; i <= n; i++){
            if(!vis[i]) post_order_dfs(i);
        }
        for(int i = inv_seq.size() - 1; i >= 0; i--){
            int u = inv_seq[i];
            if(!SCC_num[u]) inv_dfs(u, ++SCC_cnt);
        }
    }
};