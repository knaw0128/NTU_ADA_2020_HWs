#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>
#include <unordered_set>
#define F first
#define S second
using namespace std;
int n,m;
vector<int>G[1000000];
int ok[1000000];
int done[1000000];
void dfs(int x){
    if(ok[x])
        return;
    ok[x]=1;
    cout<<x<<" ";
    for(int i=0;i<G[x].size();i++){
        dfs(G[x][i]);
    }
}

int main(){
    cin>>n>>m;
    vector<pair<int,int> >s;
    while(m--){
        int a,b;
        cin>>a>>b;
        s.push_back(make_pair(a,b));
    }
    sort(s.begin(),s.end());
    for(int i=0;i<s.size();i++){
        G[s[i].F].push_back(s[i].S);
        G[s[i].S].push_back(s[i].F);
    }
    for(int a=0;a<=n;a++){
        sort(G[a].begin(),G[a].end());
    }
    dfs(1);
    cout<<endl;

    queue<int> bfs;
    bfs.push(1);
    done[1]=1;
    while(!bfs.empty()){
        vector<int> pre;
        while(!bfs.empty()){
            pre.push_back(bfs.front());
            bfs.pop();
        }
        sort(pre.begin(), pre.end());
        for(int a=0;a<pre.size();a++){
            cout<<pre[a]<<" ";
            for(int b=0;b<G[pre[a]].size();b++){
                if(done[G[pre[a]][b]])
                    continue;
                done[G[pre[a]][b]]=1;
                bfs.push(G[pre[a]][b]);
            }
        }
    }
    return 0;
}