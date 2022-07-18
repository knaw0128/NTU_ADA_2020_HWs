//ref https://www.jianshu.com/p/437bd6936dad
#include "ypglpk.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
#define MAXN 81
int clique[81][801];
int n,m,idx;

int some[MAXN][MAXN];  
int none[MAXN][MAXN]; 
int all[MAXN][MAXN];    
int mp[MAXN][MAXN];

void dfs(int d, int an, int sn, int nn){
    if(!sn && !nn){
        for(int a=0;a<an;a++)
            clique[all[d][a]-1][idx]=1;
        idx++;
        return;
    }
    int u = some[d][0];
    for(int i = 0; i < sn; ++i){
        int v = some[d][i];
        if(mp[u][v]) continue; 
        for(int j = 0; j < an; ++j){
            all[d+1][j] = all[d][j];  
        }
        all[d+1][an] = v;
        int tsn = 0, tnn = 0;
        for(int j = 0; j < sn; ++j)  if(mp[v][some[d][j]])  some[d+1][tsn++] = some[d][j];
        for(int j = 0; j < nn; ++j)  if(mp[v][none[d][j]])  none[d+1][tnn++] = none[d][j];
        dfs(d+1, an+1, tsn, tnn);
        some[d][i] = 0, none[d][nn++] = v;
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin>>t;
    pair<double,vector<double>> res;
    while(t--){
        cin>>n>>m;
        idx=0;
        memset(mp,0,sizeof(mp));
        memset(clique,0,sizeof(clique));
        memset(some,0,sizeof(some));
        for(int a=0;a<n;a++)    some[0][a]=a+1;
        for(int a=0;a<m;a++){
            int tmp1,tmp2;
            cin>>tmp1>>tmp2;
            mp[++tmp1][++tmp2]=1;
            mp[tmp2][tmp1]=1;
        }
        dfs(0,0,n,0);

        vector<vector<double>> A(n+2*idx,vector<double>(idx,0));
        vector<double> B(n+2*idx,0),C(idx,-1);
        vector<bool> isint(idx,1);

        for(int a=0;a<idx;a++){
            for(int b=0;b<n;b++){
                if(clique[b][a])    A[b][a]=-1;
            }
        }
        for(int a=0;a<n;a++)
            B[a]=-1;
        
        for(int a=0;a<idx;a++){
            A[n+2*a][a] = 1;
            A[n+2*a+1][a] = -1;
            B[n+2*a] = 1;
            B[n+2*a+1] = 0;
        }
            
        res=ypglpk::mixed_integer_linear_programming(A,B,C,isint);

        cout<<-res.first<<"\n";
        int done[100]={0};
        for(int a=0;a<idx;a++){
            if(!res.second[a]) continue;
            int peo=0;
            string out;
            for(int b=0;b<n;b++){
                if(clique[b][a]&&!done[b]){
                    done[b]=1;
                    out=out+" "+to_string(b);
                    peo++;
                }
            }
            cout<<peo<<out<<"\n";
        }

    }

    return 0;
}
