#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef pair<long long,long long> pii;
vector<pii> all;
int n,x,y,v;

int Pcmp(int a, int b){
    if(all[a].second<all[b].second||(all[a].second==all[b].second&&all[a].first<all[a].first))
        return 1;
    return 0;
}

long long int BIT[2000009]; //1 indexed
long long int ranking[2000009][2]; //p q
long long int build[2000009];
long long int P[2000009];

void buildBIT(long long int sum[]){
    int lowbit;
    for(int a=1;a<=n;a++){
        lowbit = a&(-a);
        BIT[a] = sum[a]-sum[a-lowbit];
    }
}

int query(int idx){
    int ans=0;
    while(idx){
        ans+=BIT[idx];
        idx -= idx&(-idx);
    }
    return ans;
}

void deleteBIT(int idx){
    while(idx<=n){
        BIT[idx] -= 1;
        idx += idx&(-idx);
    }
}

int main(){
    scanf("%d%d%d%d",&n,&x,&y,&v);
    all.resize(n);
    for(int a=0;a<n;a++){
        P[a] = a;
        build[a+1] = build[a]+1;
        scanf("%lld%lld",&all[a].second,&all[a].first); //p z
    }
    sort(all.begin(), all.end());
    sort(P, P+n, Pcmp);

    int qidx=0;
    for(int a=0;a<n;a++){
        ranking[P[a]][0] = a+1;
        while(qidx<n&&all[P[qidx]].second*x<=all[P[a]].second*y+v)
            qidx++;
        ranking[P[a]][1] = qidx;
    }
    buildBIT(build);
    long long int ans=0;
    int left=n;
    for(int a=0;a<n;a++){
        int start=a;
        while(a<n-1&&all[a].first==all[a+1].first){
            deleteBIT(ranking[a][0]);
            left--;
            a++;
        }
        deleteBIT(ranking[a][0]);
        left--;
        for(int b=start;b<=a;b++)
            ans+=left-query(ranking[b][1]);
    }
    printf("%lld",ans);
    return 0;
}