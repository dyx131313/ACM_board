#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<iostream>
#include<deque>
using namespace std;
typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef string str;
typedef vector<int> vec;

const int n_size=1e6+5;

int rk[n_size],oldrk[n_size],sa[n_size],oldsa[n_size],cnt[n_size],height[n_size];
char s[n_size];
int n,m; 

void get_sa(){
	for(int i=1;i<=n;i++) ++cnt[rk[i]=s[i]],m=max(m,rk[i]); 
	for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
	for(int i=n;i>=1;i--) sa[cnt[rk[i]]--]=i;
	for(int w=1,p;w<=n;w<<=1,m=p){
		p=0;
		for(int i=n-w+1;i<=n;i++) oldsa[++p]=i;
		for(int i=1;i<=n;i++) if(sa[i]>w) oldsa[++p]=sa[i]-w;
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++) ++cnt[rk[oldsa[i]]];
		for(int i=1;i<=m;i++) cnt[i]+=cnt[i-1];
		for(int i=n;i>=1;i--) sa[cnt[rk[oldsa[i]]]--]=oldsa[i];
		swap(oldrk,rk);p=0;
		for(int i=1;i<=n;i++) rk[sa[i]]=(oldrk[sa[i]]==oldrk[sa[i-1]]&&oldrk[sa[i]+w]==oldrk[sa[i-1]+w])? p:++p; 
	}
}

void get_height(){
	int k=0;
	for(int i=1;i<=n;i++){
		if(k) k--;
		while(s[i+k]==s[sa[rk[i]-1]+k]) k++;
		height[rk[i]]=k;
	}
}

int main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1);
	get_sa();
	get_height();
	for(int i=1;i<=n;i++) printf("%d ",sa[i]);
	return 0;
}