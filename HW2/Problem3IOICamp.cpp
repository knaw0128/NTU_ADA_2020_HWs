#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

struct node{
    long long int start;
    long long int end;
    long long int price;
    long long int max;
};

int mycmp(node a, node b){
    if(a.start<b.start||(a.start==b.start&&a.end<b.end))
        return 1;
    return 0;
}

int mycmpP(node a, node b){
    if(a.price>b.price)
        return 1;
    return 0;
}

bool operator<(node a, node b){
    if(a.end>b.end)
        return 1;
    return 0;
}

long long int find_ans(vector<node>& all, long long int p){
    long long int ans=0;
    sort(all.begin(), all.end(), mycmp);
    long long int n= all.size();
    long long int idx = 1, now = all[0].start;
    priority_queue<node> pqueue;
    pqueue.push(all[0]);

    while(idx<n){
        // cout<<"now = "<<now<<" ans = "<<ans<<endl;

        for(;idx<n;idx++){
            if(all[idx].start<=now)
                pqueue.push(all[idx]);
            else if(pqueue.empty()){
                pqueue.push(all[idx]);
                now = all[idx].start;
            }
            else
                break;
        }

        long long int next =  min(pqueue.top().max, pqueue.top().end-now+1);
        if(idx<n){
            next = min(next, all[idx].start-now);
        }
        ans+=next;
                
        if(idx<n&&next==all[idx].start-now){
            node same = pqueue.top();
            same.max -= next;
            if(same.max>0)
                pqueue.push(same);
        }
        now += next;
        pqueue.pop();
    }

    while(!pqueue.empty()){
        long long int next = min(pqueue.top().max, pqueue.top().end-now+1);
        ans += next;
        now += next;
        pqueue.pop();
    }

    return ans*p;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    long long int n;
    cin>>n;
    node all[3009];
    for(int a=0;a<n;a++)
        cin>>all[a].start>>all[a].end>>all[a].max>>all[a].price;
    sort(all, all+n, mycmpP);

    long long int preP = 0, nextP, ans = 0;
    while(1){
        vector<node> use;
        for(int m=0;m<n;m++){
            if(all[m].price<=preP)
                break;
            use.push_back(all[m]);
            nextP = all[m].price;
        }
        if(!use.empty())
            ans += find_ans(use, nextP-preP);
        else
            break;
        
        preP = nextP;
    }

    cout<<ans;

    return 0;
}