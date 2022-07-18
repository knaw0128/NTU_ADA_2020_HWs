#include<iostream>
#include<vector>
using namespace std;
vector<int> peg[3];
long long int times[100007]={0};

int main(){
    int n;
    cin>>n;
    for(int a=0;a<3;a++){
        int m,tmp;
        cin>>m;
        while(m--){
            cin>>tmp;
            peg[a].push_back(tmp);
        }
    }
    for(int a=1;a<n;a++)
        times[a] = (times[a-1]*2+1)%998244353;
    
    int now=0,state=0;
    long long int ans=0; //states 1 moved 0 unmoved
    int idx[3]={0};
    int bad=1;
    int str=1;

    for(int b=0;b<max(peg[0].size(), max(peg[1].size(), peg[2].size()));b++){
        for(int a=0;a<3;a++){
            if(peg[a].size()>b&&peg[a][b]%2!=(n-b%2+a%2)%2){
                cout<<"-1";
                return 0;
            }
        }
    }
    


    for(int a=n;a>0;a--){
        for(int b=0;b<3;b++){
            if(idx[b]<peg[b].size()&&peg[b][idx[b]]==a){
                if(b!=now){
                    state = (state+1)%2;
                }
                now = b;
                idx[b]++;
            }
        }
        if(!state)
            ans+=times[a-1]+1;
        ans = ans%998244353;
    }
    cout<<ans;
    return 0;
}