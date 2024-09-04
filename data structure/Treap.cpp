//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5,inf = 1e9 + 7;

class Treap{
private:
    struct node{
        int val,poi,l_son,r_son,treap_cnt,treap_size;
    };
    vector<node> t;
    int root;
    int n,cnt;
public:
    void combine_inf(int cur){
        t[cur].treap_size = t[cur].treap_cnt + t[t[cur].l_son].treap_size + t[t[cur].r_son].treap_size;
    }
    void treap_build(){
        t[++cnt] = (node){-inf,rand(),0,2,1,1};
        t[++cnt] = (node){inf,rand(),0,0,1,1};
        root = 1;
        combine_inf(root);
    }
    void right_rotate(int &cur){
        int a = t[cur].l_son;
        t[cur].l_son = t[a].r_son;
        t[a].r_son = cur;
        cur = a;
        combine_inf(t[cur].r_son);
        combine_inf(cur);
    }
    void left_rotate(int &cur){
        int a = t[cur].r_son;
        t[cur].r_son = t[a].l_son;
        t[a].l_son = cur;
        cur = a;
        combine_inf(t[cur].l_son);
        combine_inf(cur);
    }
    void treap_insert(int &cur, int val){
        if(!cur){
            t[++cnt] = (node){val,rand(),0,0,1,1};
            cur = cnt;
            return;
        }else{
            if(t[cur].val == val){
                t[cur].treap_cnt++;
                combine_inf(cur);
                return;
            }else{
                if(val < t[cur].val){
                    treap_insert(t[cur].l_son,val);
                    if(t[t[cur].l_son].poi > t[cur].poi) right_rotate(cur);
                }else{
                    treap_insert(t[cur].r_son,val);
                    if(t[t[cur].r_son].poi > t[cur].poi) left_rotate(cur);
                }
            }
        }
        combine_inf(cur);
    }
    void treap_erase(int &cur, int val){
        if(!cur) return;
        if(t[cur].val == val){
            if(t[cur].treap_cnt > 1){
                t[cur].treap_cnt--;
                combine_inf(cur);
                return;
            }else{
                if(t[cur].l_son || t[cur].r_son){
                    if(!t[cur].r_son || t[t[cur].l_son].poi > t[t[cur].r_son].poi){
                        right_rotate(cur);
                        treap_erase(t[cur].r_son,val);
                    }else{
                        left_rotate(cur);
                        treap_erase(t[cur].l_son,val);
                    }
                }else{
                    cur = 0;
                }
            }
        }else if(val < t[cur].val){
            treap_erase(t[cur].l_son,val);
        }else{
            treap_erase(t[cur].r_son,val);
        }
        combine_inf(cur);
    }
    int treap_rank(int cur, int val){
        if(!cur) return 0;
        if(t[cur].val == val) return t[t[cur].l_son].treap_size;
        else if(t[cur].val > val) return treap_rank(t[cur].l_son, val);
        else return treap_rank(t[cur].r_son, val) + t[cur].treap_cnt + t[t[cur].l_son].treap_size;
    }
    int treap_query(int cur, int rnk){
        if(!cur) return inf;
        if(rnk <= t[t[cur].l_son].treap_size) return treap_query(t[cur].l_son,rnk);
        else if(rnk > t[t[cur].l_son].treap_size + t[cur].treap_cnt) return treap_query(t[cur].r_son,rnk - t[t[cur].l_son].treap_size - t[cur].treap_cnt);
        else return t[cur].val;
    }
    int treap_pre(int cur, int val){
        int ans = 1;//-inf
        while(cur){
            if(t[cur].val == val){
                if(t[cur].l_son){
                    cur = t[cur].l_son;
                    while(t[cur].r_son) cur = t[cur].r_son;
                    ans = cur;
                }else{
                    break;
                }
            }
            if(t[cur].val < val && t[cur].val > t[ans].val) ans = cur;
            cur = val < t[cur].val ? t[cur].l_son : t[cur].r_son;
        }
        return t[ans].val;
    }
    int treap_suc(int cur, int val){
        int ans = 2;//inf
        while(cur){
            if(t[cur].val == val){
                if(t[cur].r_son){
                    cur = t[cur].r_son;
                    while(t[cur].l_son) cur = t[cur].l_son;
                    ans = cur;
                }else{
                    break;
                }
            }
            if(t[cur].val > val && t[cur].val < t[ans].val) ans = cur;
            cur = val < t[cur].val ? t[cur].l_son : t[cur].r_son;
        }
        return t[ans].val;
    }
    void init(int cur_n){
        n = cur_n;
        t.resize(n + bias);
        cnt = 0;
        treap_build();
    }
};

/*
int main(){
    srand(inf);
}
*/