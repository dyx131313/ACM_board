//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5, inf = 2e9;

class Dinic{
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
    deque<int> que;
    vector<int> vis, cur, path;
    Chain_forward G;
    int n, m, S, T, cnt = 1;
    int ans = 0;
public:
    void init(int cur_n, int cur_m, int cur_S, int cur_T){
        n = cur_n;
        m = cur_m;
        S = cur_S;
        T = cur_T;
        vis.resize(n + bias);
        cur.resize(n + bias);
        path.resize(n + bias);
        G.init(n, m);
    }
    void add_edge(int a, int b, ll c){
        G.add_edge(a, b, c);
        G.add_edge(b, a, 0ll);
    }
    bool find_augmenting_path(){
        int curr;
        fill(vis.begin(), vis.end(), 0);
        fill(path.begin(), path.end(), 0);
        vis[S] = 1;
        que.clear();
        que.push_back(S);
        while(!que.empty()){
            curr = que.front();
            que.pop_front();
            for(int i = G.head[curr]; i; i = G.e[i].nex){
                if(G.e[i].weight && !vis[G.e[i].to]){
                    path[G.e[i].to] = i;
                    vis[G.e[i].to] = 1;
                    que.push_back(G.e[i].to);
                }
            }
            if(vis[T]) return true;
        }
        return vis[T];
    }
    ll Maxflow(){
        ll flo;
        while(find_augmenting_path()){
            flo = inf;
            for(int i = T; i != S; i = G.e[path[i] ^ 1].to) flo = min(flo, G.e[path[i]].weight);
            for(int i = T; i != S; i = G.e[path[i] ^ 1].to) G.e[path[i]].weight -= flo, G.e[path[i] ^ 1].weight += flo;
            ans += flo;
        }
        return ans;
    }
};