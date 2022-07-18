//Ref 和李長諺討論
#include<bits/stdc++.h>
using namespace std;
vector<long long int> G[100009];
vector<long long int> reG[100009];
vector<long long int> SCC_G[100009];
vector<long long int> all_SCC[100009];
vector<pair<int,int>> add_pair;
stack<long long int> order;
long long int col[100009];//each vertice's group
long long int ver[100009];
long long int done[100009];
long long int cnt,n,m;
int indegree[100009];
int outdegree[100009];

void init(){
    for(int a=1;a<=n;a++){
        G[a].clear();
        reG[a].clear();
        SCC_G[a].clear();
        all_SCC[a].clear();
        col[a]=0;
        ver[a]=0;
        done[a]=0;
        indegree[a]=1;
        outdegree[a]=1;
    }
    while(!order.empty())
        order.pop();
    cnt=0;
    add_pair.clear();
}

void dfs(vector<long long int> graph[],long long int now,long long int B){
    done[now]=1;
    if(!B){
        col[now]=cnt;
        all_SCC[cnt].push_back(now);
    }
    for(int a=0;a<graph[now].size();a++){
        if(!done[graph[now][a]])
            dfs(graph,graph[now][a],B);
    }
    if(B){
        order.push(now);
    }
}

void getorder(){
    for(int a=1;a<=n;a++){
        if(!done[a])
            dfs(reG,a,1);
    }
}

void getSCC(){
    memset(done,0,sizeof(done));
    while(!order.empty()){
        int u=order.top();order.pop();
        if(done[u])
            continue;
        ver[++cnt]=u;
        dfs(G,u,0);
    }
}

long long int find_edge(){
    if(cnt==1)
        return 0;
    long long int ans_out=0;
    long long int ans_in=cnt;
    for(int a=1;a<=cnt;a++){
        if(SCC_G[a].size()==0)
            ans_out++;
        else
            outdegree[a]=0;
        for(int b=0;b<SCC_G[a].size();b++){
            if(indegree[SCC_G[a][b]]){
                indegree[SCC_G[a][b]]=0;
                ans_in--;
            }
        }
    }
    return max(ans_in,ans_out);
}

int dfs_1(int now){
    if(done[now])
        return 0;
    done[now]=1;
    if(outdegree[now])
        return now;
    int ret=0;
    for(int a=0;a<SCC_G[now].size();a++){
        if(done[SCC_G[now][a]])
            continue;
        ret=dfs_1(SCC_G[now][a]);
        if(ret){
            return ret;
        }
    }
    return 0;
}

void find_pair(){
    if(cnt==1)
        return;
    memset(done,0,sizeof(long long int)*(cnt+5));
    vector<int> orphan;
    vector<int> head;//in==1
    vector<int> tail;//out==1
    vector<pair<int,int>> match;
    stack<int> sinHead;
    stack<int> sinTail;
    int last_t,last_h;
    for(int a=1;a<=cnt;a++){
        if(indegree[a]&&outdegree[a])
            orphan.emplace_back(a);
        else if(indegree[a])
            head.emplace_back(a);
        else if(outdegree[a])
            tail.emplace_back(a);
    }
    if(head.empty()&&tail.empty()){
        for(int a=1;a<orphan.size();a++)
            add_pair.push_back(make_pair(orphan[a-1],orphan[a]));
        add_pair.push_back(make_pair(orphan.back(),orphan[0]));
        return;
    }
    while(!orphan.empty()){
        outdegree[tail[0]]=0;
        indegree[orphan.back()]=0;
        add_pair.push_back(make_pair(tail[0],orphan.back()));
        SCC_G[tail[0]].push_back(orphan.back());
        tail[0]=orphan.back();
        orphan.pop_back();
    }
    
    for(int a=0;a<head.size();a++){
        int end=dfs_1(head[a]);
        if(end!=0){
            match.push_back(make_pair(head[a],end));
            indegree[head[a]]=0;
            outdegree[end]=0;
        }
    }
    for(int a=1;a<=cnt;a++){
        if(indegree[a])
            sinHead.push(a);
        if(outdegree[a])
            sinTail.push(a);
    }

    for(int a=1;a<match.size();a++)
        add_pair.push_back(make_pair(match[a-1].second,match[a].first));
    add_pair.push_back(make_pair(match.back().second,match[0].first));

    while (!sinHead.empty()||!sinTail.empty()){
        if(sinHead.empty()){
            while(!sinTail.empty()){
                add_pair.push_back(make_pair(sinTail.top(),match[0].second));
                sinTail.pop();
            }
            break;
        }
        if(sinTail.empty()){
            while(!sinHead.empty()){
                add_pair.push_back(make_pair(match[0].first,sinHead.top()));
                sinHead.pop();
            }
            break;
        }
        add_pair.push_back(make_pair(sinTail.top(),sinHead.top()));
        sinHead.pop();sinTail.pop();
    }

}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t,flag;
    cin>>t>>flag;
    for(int a=0;a<t;a++){
        cin>>n>>m;
        if(n==1){
            cout<<"0\n";
            continue;
        }
        init();
        for(int b=0;b<m;b++){
            int u,v;
            cin>>u>>v;
            G[u].push_back(v);
            reG[v].push_back(u);
        }
        getorder();
        getSCC();
        
        for(int a=1;a<=cnt;a++){
            map<long long int,int> tmp;tmp[a]=1;
            for(int b=0;b<all_SCC[a].size();b++){
                long long int now=all_SCC[a][b];
                for(int c=0;c<G[now].size();c++){
                    if(tmp.find(col[G[now][c]])!=tmp.end())
                        continue;
                    tmp[col[G[now][c]]]=1;
                    SCC_G[a].push_back(col[G[now][c]]);
                }
            }
        }
        cout<<find_edge()<<endl;
        if(flag){
            find_pair();
            for(int a=0;a<add_pair.size();a++)
                cout<<ver[add_pair[a].first]<<" "<<ver[add_pair[a].second]<<endl;
        }
    }

    return 0;
}
