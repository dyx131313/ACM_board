#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

typedef long long int ll;

const int n_size=1e5+5;

int n;
ll A[n_size],md[n_size],mi[n_size],M=1;//a % md[i] = a[i], M=pie(md[i]), mi[i]=M/md[i]

ll exgcd(ll a,ll b,ll &x,ll &y){
    if(!b){
        x=1,y=0;
        return a;
    }
    ll ret=exgcd(b,a%b,x,y);
    ll t=x;x=y;y=t-a/b*y;
    return ret;
}

ll subtask1(){
    ll ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lld%lld",&md[i],&A[i]);
        M*=md[i];
    }
    for(int i=1;i<=n;i++){
        ll inv,t;
        exgcd(M/md[i],md[i],inv,t);
        inv=((inv%md[i])+md[i])%md[i];
        ans=(ans+A[i]*(M/md[i])*inv)%M;
    }
    return ans;
}//when mod numbers are coprime

ll slow_mul(ll a,ll b,ll c){
    ll ret=0;
    for(;b;b>>=1){
        if(b&1) ret=(ret+a)%c;
        a=a*2%c;
    }
    return ret;
}//mul for large number

ll subtask2(){
    scanf("%d",&n);
    ll c_md=1,c_A=0;
    for(int i=1;i<=n;i++){
        ll x,y;
        scanf("%lld%lld",&md[i],&A[i]);
        ll gcd=exgcd(c_md,md[i],x,y);ll lcm=c_md/gcd*md[i];
        ll AA=((A[i]-c_A)%md[i]+md[i])%md[i];
        // ll AA=(A[i]-c_A);
        if(AA%gcd!=0) return -1;
        x=(x%lcm+lcm)%lcm;
        x=slow_mul(x,AA/gcd,lcm);
        c_A=(slow_mul(x,c_md,lcm)+c_A+lcm)%lcm;
        c_md=lcm;
        // printf("c_A=%lld c_md=%lld\n",c_A);
    }
    return c_A;

}// when mod numbers are not coprime

int main(){
    printf("%lld",subtask2());
    return 0;
}