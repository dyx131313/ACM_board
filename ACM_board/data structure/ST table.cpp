#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<stack>
#include<set>
#include<map>
#include<cstring>
#include<deque>
#include<vector>
#include<iostream>
using namespace std;

typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;

const int n_size=1e6+5;

int n,m,st[n_size][30],s[n_size],log_2[n_size];

int deal(int x,int y){return  max(st[y][log_2[y-x]],st[x+(1<<(log_2[y-x]))-1][log_2[y-x]]);} 

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	scanf("%d %d",&n,&m);
	log_2[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&s[i]);
		st[i][0]=s[i];
		if(i!=1) log_2[i]=log_2[i/2]+1;
	}
	for(int i=1,x,y;i<=m;i++){
		scanf("%d %d",&x,&y);
		printf("%d\n",deal(x,y));
	}
	return 0;
}
