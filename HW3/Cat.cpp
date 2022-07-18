//Ref 和李長諺討論
#include<bits/stdc++.h>
using namespace std;
int djs[300009];
int cat[300009];
int t_num[300009];
int find(int a){
    if(djs[a]==a)
        return a;
    return djs[a]=find(djs[a]);
}
void U(int a,int b){
    a=find(a);
    b=find(b);
    djs[b]=a;
}

int main(){
    int n,q;
    scanf("%d%d",&n,&q);
    map<int,long long int> number;
    map<int,int> root;
    long long int sum=0;
    int end=n+1;
    for(int a=1;a<=n;a++){
        djs[a]=a;
        t_num[a]=a;
        int tmp;
        scanf("%d",&tmp);
        if(number.find(tmp)==number.end()){
            number[tmp]=1;// numbers of member    root
            root[tmp]=a;
            cat[a]=tmp;
        }
        else{
            sum-=(number[tmp]*(number[tmp]-1)/2);
            number[tmp]++;
            U(root[tmp],a);
            sum+=(number[tmp]*(number[tmp]-1)/2);
        }
    }
    for(int a=0;a<q;a++){
        int order;
        scanf("%d",&order);
        if(order==1){
            int p,r;
            scanf("%d%d",&p,&r);
            int k=max(p-r,1);
            if(number.find(p)==number.end()){
                number[p]=0;
                root[p]=0;
            }
            sum-=((number[p])*(number[p]-1)/2);
            for(map<int,long long int>::iterator tmp=number.lower_bound(k);tmp!=number.end()&&tmp->first<=p+r;){
                int now=tmp->first;
                if(now==p){
                    tmp++;
                    continue;
                }
                if(number[p]==0){
                    root[p]=root[now];
                    cat[root[p]]=p;
                }
                number[p]+=tmp->second;
                sum-=((tmp->second)*(tmp->second-1)/2);
                U(root[p],root[now]);
                root.erase(now);
                number.erase(tmp++);
            }
            sum+=number[p]*(number[p]-1)/2;
            if(number[p]==0){
                number.erase(p);
                root.erase(p);
            }
            printf("%lld\n",sum);            
        }
        else if(order==2){
            int t,x;
            cin>>t>>x;
            int origin=cat[find(t_num[t])];
            t_num[t]=end++;
            djs[t_num[t]]=t_num[t];
            if(root.find(x)==root.end()){
                root[x]=t_num[t];
                number[x]=0;
                cat[t_num[t]]=x;
            }
            else{
                U(root[x],t_num[t]);
            }
            sum-=(number[x]*(number[x]-1)/2);
            sum-=(number[origin]*(number[origin]-1)/2);
            number[x]++;
            number[origin]--;
            sum+=(number[x]*(number[x]-1)/2);
            sum+=(number[origin]*(number[origin]-1)/2);
            if(number[origin]==0){
                number.erase(origin);
                root.erase(origin);
            }
            printf("%lld\n",sum);

        }
    }


    return 0;
}