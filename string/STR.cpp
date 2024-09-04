//code_board
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;
typedef string str;

const int bias = 5;

class basic_str{
public:
    class KMP{
    private:
        str a, b;
        int len_a, len_b;
    public:
        void init(str cur_a, str cur_b){
            cur_a = " " + cur_a, cur_b = " " + cur_b;
            a = cur_a, b = cur_b;
            len_a = a.size(), len_b = b.size();
        }
        vec get_pre(){
            vec pre(len_a + bias, 0);
            for(int i = 2, j = 0; i < len_a; i++){
                while(j && a[j + 1] != a[i]) j = pre[j];
                if(a[j + 1] == a[i]) pre[i] = ++j;
            }
            return pre;
        }
        vec find_match(vec pre){
            vec ans; 
            for(int i = 1, j = 0; i < len_b; i++){
                while(j && a[j + 1] != b[i]) j = pre[j];
                if(a[j + 1] == b[i]) j++;
                if(j == len_a) ans.push_back(i - len_a + 1);
            }
            return ans;
        }
    };

    class MANACHER{
    private:
        str a, aa;
        int len_aa;
        vec sym_len;
    public:
        void init(str cur_a){
            a = cur_a;
            aa = "#";
            for(int i = 0; a[i] != '\0'; i++) aa += a[i], aa += "#";
            aa += "\0";
            len_aa = aa.size();
        }
        void manacher(){
            sym_len.resize(len_aa);
            for(int i = 1, l = 1, r = 1; i < len_aa; i++){
                if(i < r) sym_len[i] = min(r - i + 1, sym_len[l + r - i]);
                else sym_len[i] = 1;
                while(i - sym_len[i] && i + sym_len[i] < len_aa && aa[i - sym_len[i]] == aa[i + sym_len[i]]) sym_len[i]++;
                if(r < i + sym_len[i] - 1){
                    r = i + sym_len[i] - 1;
                    l = 2 * i - r;
                }
            }
        }
    };
};