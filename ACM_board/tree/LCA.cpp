//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class online_double{
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
            e.resize(2 * m + bias);
        }
        void add_edge(int a, int b, int c){
            e[++cnt].to = b;
            e[cnt].nex = head[a];
            e[cnt].weight = c;
            head[a] = cnt;
        }
    };
    Chain_forward G;
    vec dep,lg;
    vector<vec> anc;
    int n, root;
public:
    void init(int cur_n){
        n = cur_n;
        dep.resize(n + bias);
        lg.resize(n + bias);
        for(int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        anc.resize(20, vec(n + bias));
        G.init(n, 2 * n);
    }
    void add_edge(int a, int b){
        G.add_edge(a, b, 1);
        G.add_edge(b, a, 1);
    }
    void dfs(int u, int fa){
        dep[u] = dep[fa] + 1;
        for(int i = 0; i <= lg[dep[u]]; i++) anc[i][u] = (i == 0) ? fa : anc[i - 1][anc[i - 1][u]];
        for(int i = G.head[u], v; i; i = G.e[i].nex){
            v = G.e[i].to;
            if(v != fa) dfs(v, u);
        }
    }
    int query(int a, int b){
        if(dep[a] > dep[b]) swap(a, b);
        for(int i = lg[dep[b] - dep[a]]; i >= 0; i--) if((1 << i) <= dep[b] - dep[a]) b = anc[i][b];
        if(a == b) return b;
        for(int i = lg[dep[a]]; i >= 0; i--) if(anc[i][b] != anc[i][a]) a = anc[i][a], b = anc[i][b];
        return anc[0][a];
    }
};

class offline_tarjan{
private:
    class Chain_forward{
    public:
        struct edge{
            int to, nex;
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
        void add_edge(int a, int b){
            e[++cnt].to = b;
            e[cnt].nex = head[a];
            head[a] = cnt;
        }
    };
    Chain_forward G;
    vec dep, ans;
    vector<vector<pa> > query;
    vec vis;
    int n, q, root;
    int cnt = 0;
    class Union{
    private: 
        int n;
        vec anc;
    public:
        void init(int cur_n){
            n = cur_n;
            anc.resize(n + bias);
            for(int i = 1; i <= n; i++) anc[i] = i;
        }
        int find(int k){
            if(anc[k] == k) return anc[k];
            return anc[k] = find(anc[k]);
        }
        void merge(int a, int b){
            anc[find(a)] = find(b);
        }
    };
    Union U;
public: 
    void init(int cur_n, int cur_q, int cur_root){
        n = cur_n;
        q = cur_q;
        root = cur_root;
        dep.resize(n + bias);
        ans.resize(q + bias);
        vis.resize(n + bias);
        U.init(n);
        G.init(n, 2 * n);
        query.resize(n);
    }
    void add_edge(int a, int b){
        G.add_edge(a, b);
        G.add_edge(b, a);
    }
    void add_query(int a, int b){
        query[a].push_back(make_pair(b, cnt));
        query[b].push_back(make_pair(a, cnt));
    }
    void dfs(int u, int fa){
        for(int i = G.head[u], v; i; i = G.e[i].nex){
            v = G.e[i].to;
            if(v != fa) continue;
            dfs(v, u);
        }
        for(int i = 0; i < (int)query[u].size(); i++){
            if(vis[query[u][i].second]) ans[query[u][i].second] = U.find(query[u][i].first);
            else vis[query[u][i].second] = 1;
        }
        if(fa != -1) U.merge(u, fa);
    }
};