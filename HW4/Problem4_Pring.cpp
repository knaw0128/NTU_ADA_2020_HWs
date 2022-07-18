//和沈立程 李長諺討論
#include <iostream>
#include <vector>
using namespace std;
#define int long long
#define INF 999999999999
int dp1[1002][1002][2];
int dp2[1002][1002][2];
struct cut{
    int line;
    int front;
    int back;
    cut(){
        line=front=back=0;
    }
};

int64_t find(int a,int b,int c){
    return b*((a&b)^(b|c)^(a+c));
}

 main(){
    int n,m;
    cin>>n>>m;
    vector<int> symbol;
    vector<cut> over;
    int sum=0;
    for(int a=0;a<n;a++){
        int tmp;
        cin>>tmp;
        symbol.push_back(tmp);
    }
    
    for(int a=0;a<n;a++){
        cut row;
        row.line=-abs(symbol[a]-symbol[(a-1+n)%n]);
        row.back=find(symbol[(a-1+n)%n],symbol[a],symbol[(a+1)%n]);
        row.front=find(symbol[(a-2+n)%n],symbol[(a-1+n)%n],symbol[a]);
        sum+=symbol[a]+row.line+row.back;
        over.push_back(row);
    }
    
    if(n==2){
        cout<<symbol[0]+symbol[1];
        return 0;
    }
    
    for(int a=1;a<=m;a++)
        for(int b=0;b<=n;b++){
            dp1[a][b][0]=-INF;
            dp2[a][b][0]=-INF;
            dp1[a][b][1]=-INF;
            dp2[a][b][1]=-INF;
        }
    for(int a=0;a<n;a++){
        dp1[0][a][1]=-INF;
        dp2[0][a][1]=-INF;
    }

    dp1[1][0][1]=over[0].front+over[0].back+over[0].line;
    for(int a=1;a<=m;a++){
        for(int b=1;b<n;b++){
            if(b==1){
                dp1[a][b][0]=dp1[a][b-1][1];
                dp1[a][b][1]=dp1[a-1][b-1][1]+over[b].line+over[b].back;
                continue;
            }
            dp1[a][b][0]=max(dp1[a][b-1][0],dp1[a][b-1][1]);
            if(b!=n-1)
                dp1[a][b][1]=max(dp1[a-1][b-1][0]+over[b].line+over[b].back+over[b].front,dp1[a-1][b-1][1]+over[b].line+over[b].back);
            else
                dp1[a][b][1]=max(dp1[a-1][b-1][0]+over[b].line+over[b].front,dp1[a-1][b-1][1]+over[b].line);
        }
    }

    for(int a=1;a<=m;a++){
        for(int b=1;b<n;b++){
            dp2[a][b][0]=max(dp2[a][b-1][0],dp2[a][b-1][1]);
            if(b==1)
                dp2[a][b][1]=dp2[a-1][b-1][0]+over[b].line+over[b].back+over[b].front;
            else
                dp2[a][b][1]=max(dp2[a-1][b-1][0]+over[b].line+over[b].back+over[b].front, dp2[a-1][b-1][1]+over[b].line+over[b].back);
        }
    }
    
    int minus=-INF;
    for(int a=0;a<n;a++)
        minus=max(minus,max(dp1[m][a][0],dp1[m][a][1]));
    for(int a=0;a<n;a++)
        minus=max(minus,max(dp2[m][a][0],dp2[m][a][1]));

    cout<<sum-minus;
    
    return 0;
}