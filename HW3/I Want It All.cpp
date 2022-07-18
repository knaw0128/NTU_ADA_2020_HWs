//Ref 和李長諺討論
#include<bits/stdc++.h>
using namespace std;
vector<vector<vector<long long int>>> G(300009);
vector<vector<long long int>> all_edge;
long long int Dis[300009][2],djs[300009];
long long int edges[300009],done[300009];

struct CMP{
    bool operator()(vector<long long int>& a,vector<long long int>& b){
        return tie(a[1],edges[a[2]])>tie(b[1],edges[b[2]]);
    }
};

int mycmp(vector<long long int>& a,vector<long long int>& b){
    return a[1]<b[1];
}

int find(int x){
    if(djs[x]==x)
        return x;
    return djs[x]=find(djs[x]);
}

void U(int x,int y){
    x=find(x);
    y=find(y);
    djs[x]=y;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int a=1;a<=m;a++){
        int x,y,c;
        cin>>x>>y>>c;
        edges[a]=c;
        vector<long long int> tmp(3);
        tmp[1]=c;tmp[2]=a;
        tmp[0]=y;
        G[x].emplace_back(tmp);
        tmp[0]=x;
        G[y].emplace_back(tmp);
        tmp[2]=y;
        all_edge.emplace_back(tmp);
    }
    sort(all_edge.begin(),all_edge.end(),mycmp);
    priority_queue<vector<long long int>,vector<vector<long long int>>,CMP> P;
    for(int a=1;a<=n;a++){
        Dis[a][0]=999999999999999LL;
        djs[a]=a;
        vector<long long int> tmp(3);
        tmp[0]=a;tmp[1]=999999999999999LL;tmp[2]=0;
        if(a==1)
            tmp[1]=0;
        P.emplace(tmp);
    }

    Dis[1][0]=0;
    while(!P.empty()){
        vector<long long int> tmp=P.top();P.pop();
        int now=tmp[0];
        if(done[now])
            continue;
        done[now]=1;
        for(int a=0;a<G[now].size();a++){
            if(Dis[now][0]+G[now][a][1]<Dis[G[now][a][0]][0]){
                Dis[G[now][a][0]][0]=Dis[now][0]+G[now][a][1];
                Dis[G[now][a][0]][1]=G[now][a][2];
                vector<long long int> tmp2(3);
                tmp2[0]=G[now][a][0];tmp2[1]=Dis[G[now][a][0]][0];
                tmp2[2]=G[now][a][2];
                P.emplace(tmp2);
            }
            else if(Dis[now][0]+G[now][a][1]==Dis[G[now][a][0]][0]&&edges[Dis[G[now][a][0]][1]]>edges[G[now][a][2]]){
                Dis[G[now][a][0]][1]=G[now][a][2];
                vector<long long int> tmp2(3);
                tmp2[0]=G[now][a][0];tmp2[1]=Dis[G[now][a][0]][0];
                tmp2[2]=G[now][a][2];
                P.emplace(tmp2);
            }
        }
    }
    long long int short_sum=0;
    for(int a=1;a<=n;a++){
        short_sum+=edges[Dis[a][1]];
    }

    long long int mini_sum=0;
    for(int a=0;a<m;a++){
        long long int x=all_edge[a][0],y=all_edge[a][2];
        if(find(x)==find(y))
            continue;
        mini_sum+=all_edge[a][1];
        U(x,y);
    }
    if(mini_sum!=short_sum){
        cout<<"No";
    }
    else{
        cout<<"Yes\n";
        for(int a=2;a<=n;a++)
            cout<<Dis[a][1]<<" ";
    }

    return 0;
}