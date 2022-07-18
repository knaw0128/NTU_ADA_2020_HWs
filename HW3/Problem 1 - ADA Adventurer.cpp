//Ref 和李長諺討論
#include<bits/stdc++.h>
using namespace std;
int n, done[200009];
vector<vector<vector<int>>> G(200009);//max length
vector<vector<vector<int>>> subtree(200009);

int edgecmp(vector<int>& a,vector<int>& b){
    return a[1]>b[1];
}

int subcmp(vector<int>& a,vector<int>& b){
    return a[2]>b[2];
}

int dfs(int start, int pre){ //return max path
    if(done[start]){
        if(G[start].size()>1)
            return (G[start][0][0]==pre)?G[start][1][1]+1:G[start][0][1]+1;
        return (G[start][0][0]==pre)?1:G[start][0][1]+1;
    }
    int max_way=1;
    for(int a=0;a<G[start].size();a++){
        if(G[start][a][0]==pre||G[start][a][1]!=0){
            if(G[start][a][0]!=pre){
                max_way=max(max_way, G[start][a][1]+1);
            }
            continue;
        }
        G[start][a][1]=dfs(G[start][a][0], start);//longest route
        max_way=max(max_way, G[start][a][1]+1);
    }
    return max_way;
}

int dfs_tree(int start, int pre){ //return max subtree
    if(done[start]){
        int edge=1, did=2;
        for(int a=0;a<min(3,(int)G[start].size())&&did>0;a++){
            if(pre==G[start][a][0])
                continue;
            edge+=G[start][a][1];
            did--;
        }
        int sub=subtree[start][0][2];
        if(pre==subtree[start][0][0]){
            if(subtree[start].size()>1)
                sub=subtree[start][1][2];
            else 
                sub=1;
        }
        return max(edge,sub);
    }
    int max_size=1;
    int l1_r=0,l2_r=0;
    for(int a=0;a<subtree[start].size();a++){
        if(subtree[start][a][0]==pre||subtree[start][a][2]!=0){
            if(subtree[start][a][0]!=pre){
                max_size=max(max_size,subtree[start][a][2]);
                if(G[start][a][1]>=l1_r){
                    l2_r=l1_r;
                    l1_r=G[start][a][1];
                }
                else if(G[start][a][1]>l2_r){
                    l2_r=G[start][a][1];
                }
            }
            continue;
        }
        subtree[start][a][2]=dfs_tree(subtree[start][a][0], start);//longest route
        max_size=max(max_size, subtree[start][a][2]);
        if(G[start][a][1]>=l1_r){
            l2_r=l1_r;
            l1_r=G[start][a][1];
        }
        else if(G[start][a][1]>l2_r){
            l2_r=G[start][a][1];
        }

    }
    return max(max_size, l1_r+l2_r+1);
}

int dfs_find(int start, int pre, int ans, int max_up){
    for(int b=0;b<G[start].size();b++){
        if(G[start][b][0]==pre)
            continue;
        int edge=1,sub=0,did=2;
        for(int a=0;a<min(3,(int)G[start].size())&&did>0;a++){
            if(a==b)
                continue;
            did--;
            edge+=G[start][a][1];
        }
        if(subtree[start][0][0]!=G[start][b][0])
            sub=subtree[start][0][2];
        else if(subtree[start].size()>1)
            sub=subtree[start][1][2];
        max_up=max(max_up, max(edge,sub));
        ans=min(ans, max(G[start][b][2]/2+max_up/2+1,max(max_up,G[start][b][2])-1));
        ans=min(ans,dfs_find(G[start][b][0], start, ans, max_up));
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int a=1;a<n;a++){
        int x,y;
        cin>>x>>y;
        vector<int> tmp(3,0);
        tmp[0]=y;
        G[x].push_back(tmp);
        subtree[x].push_back(tmp);
        tmp[0]=x;
        G[y].push_back(tmp);
        subtree[y].push_back(tmp);
    }

    queue<int> bfs;
    bfs.push(1);
    while(!bfs.empty()){
        int now=bfs.front();bfs.pop();
        dfs(now,0);
        dfs_tree(now,0);
        done[now]=1;
        for(int a=0;a<G[now].size();a++){
            subtree[now][a][1]=G[now][a][1];
            G[now][a][2]=subtree[now][a][2];
            if(done[G[now][a][0]])
                continue;
            bfs.push(G[now][a][0]);
        }
        sort(subtree[now].begin(),subtree[now].end(),subcmp);
        sort(G[now].begin(),G[now].end(),edgecmp);
    }
    cout<<dfs_find(1,-1,1000000,-1); 
    return 0;
}