#include<iostream>
#include<vector>
using namespace std;
// ref:https://leetcode.com/problems/maximum-alternating-subsequence-sum/discuss/1298499/JavaC%2B%2BPython-Best-Time-to-Buy-and-Sell-Stock
long long int maxi(long long int a, long long int b, long long int c){
    if(a>=b&&a>=c)
        return a;
    if(b>=a&&b>=c)
        return b;
    return c;
}

int main(){
    int flag, t;
    cin>>t>>flag;
    int n;
    for(int i=0;i<t;i++){
        cin>>n;
        vector<pair<long long int, int>> candy;
        long long int tmp, ans=-1000000000, idx=1;
        int now=1;
        for(int a=0;a<n;a++){
            cin>>tmp;
            int cap = candy.size()-1;
            if(tmp>ans){
                ans = tmp;
                idx = a+1;
            }
            pair<long long int, int> ne;
            ne.first = tmp;
            ne.second = a+1;
            if((now*tmp>0||(cap>=0&&tmp==0&&candy[cap].first>0))){
                candy.push_back(ne);
                now *= (-1);
            }
            else if(cap>=0&&tmp>candy[cap].first){
                candy[cap] = ne;
            }
            
        }
        
        while(!candy.empty()&&candy.back().first<=0)
            candy.pop_back();

        if(candy.empty()){
            cout<<ans<<endl;
            if(flag)
                cout<<"1 "<<idx<<endl;
            continue;
        }
        
        long long int even=candy[0].first, odd=0;
        vector<long long int> seq[2];
        seq[0].push_back(candy[0].second);
        for(int a=1;a<candy.size();a++){
            if(a%2==0){
                long long int next = maxi(even, odd+candy[a].first, candy[a].first);
                if(flag&&next!=even){
                    if(next==candy[a].first)
                        seq[0].clear();
                    else if(next==odd+candy[a].first)
                        seq[0].swap(seq[1]);
                    seq[0].push_back(candy[a].second);
                }
                even = next;
            }
            else{
                long long int next = maxi(odd, even+candy[a].first, candy[a].first);
                if(flag&&next!=odd){
                    if(next==candy[a].first)
                        seq[1].clear();
                    else if(next==even+candy[a].first)
                        seq[0].swap(seq[1]);
                    seq[1].push_back(candy[a].second);
                }
                odd = next;
            }
        }
        cout<<even<<endl;
        if(flag){
            cout<<seq[0].size()<<" ";
            for(int a=0;a<seq[0].size();a++)
                cout<<seq[0][a]<<" ";
            cout<<endl;
        }
  
    }
    return 0;
}