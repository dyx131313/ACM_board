#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<vector>
#include<deque>
#include<iostream>
using namespace std;

typedef long long int ll;
typedef double db;
typedef pair<int,int> pa;
typedef vector<int> vec;

const int n_size=2e7+5;
int l1,l2,len,z[2*n_size],l,r;
string a,b,s;

int main(){
	cin>>a>>b;
	l1=a.length(),l2=b.length();
	s='@'+b+'#'+a;
	len=l1+1+l2;
	z[1]=1;l=1,r=1;
	for(int i=2;i<=len;i++){
		if(i<=r){
			if(z[i-l+1]<(r-i+1)) z[i]=z[i-l+1];
			else{
				z[i]=r-i+1;
				while(i+z[i]<=len&&s[i+z[i]]==s[1+z[i]]) z[i]++;
			}
		}else while(i+z[i]<=len&&s[i+z[i]]==s[1+z[i]]) z[i]++;
		if(z[i]&&r<=i+z[i]-1){
			r=i+z[i]-1;
			l=i;
		}
	}
	z[1]=l2;
	ll ret=0;
	for(int i=1;i<=l2;i++) ret=ret^((ll)i*(z[i]+1));
	printf("%lld\n",ret);
	ret=0;
	for(int i=l2+2;i<=l2+l1+1;i++) ret=ret^((ll)(i-l2-1)*(z[i]+1)); 
	printf("%lld\n",ret);
	return 0;
}
