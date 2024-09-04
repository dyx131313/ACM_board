//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class Cut_vertex{
private:
    class Chain_forward{
    public:
        struct edge{
            int to, nex;
            ll weight;
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
            e.resize(2 * m + bias);
        }
        void add_edge(int a, int b, ll c){
            e[++cnt].to = b;
            e[cnt].nex = head[a];
            e[cnt].weight = c;
            head[a] = cnt;
        }
    };
    vector<int> dfn, low, cut_vertex;
    Chain_forward G;
    int n, m, cnt = 1, dfn_clo = 0;
public:
    void init(int cur_n, int cur_m){
        n = cur_n;
        m = cur_m;
        dfn.resize(n + bias);
        fill(dfn.begin(), dfn.end(), 0);
        low.resize(n + bias);
        fill(low.begin(), low.end(), 0);
        cut_vertex.resize(n + bias);
        fill(cut_vertex.begin(), cut_vertex.end(), 0);
        G.init(n, m);
        dfn_clo = 0;
    }
    void add_edge(int a, int b){
        G.add_edge(a, b, 1);
    }
    void dfn_dfs(int u, int fa){
        dfn[u] = low[u] = ++dfn_clo;
        int dfn_son = 0;
        for(int i = G.head[u]; i; i = G.e[i].nex){
            int v = G.e[i].to;
            if(v != fa){
                if(dfn[v]){
                    low[u] = min(low[u], dfn[v]);
                }else{
                    dfn_son++;
                    dfn_dfs(v, u);
                    low[u] = min(low[u], low[v]);
                    if(low[v] >= dfn[u]) cut_vertex[u] = 1;
                }
            }
        }
        if(fa == -1 && dfn_son == 1) cut_vertex[u] = 0;
    }
    void solve(){
        for(int i = 1; i <= n; i++) if(!dfn[i]) dfn_dfs(i, -1);
        int cnt_cut_vertex = 0;
        for(int i = 1; i <= n; i++) cnt_cut_vertex += cut_vertex[i];
    }
};