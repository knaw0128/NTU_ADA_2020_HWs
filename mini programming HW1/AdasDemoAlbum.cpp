#include<iostream>
using namespace std;
long long int bar[200006];
int n,x,y,z;
long long int prefix[200006];

long long int pre(int a, int b){
    long long int ans = bar[a]*x;
    ans+=(prefix[b]-prefix[a])*y;
    return ans;
}

long long int back(int a, int b){
    long long int ans = bar[b]*z;
    ans+=(prefix[b-1]-prefix[a]+bar[a])*y;
    return ans;
}

long long int find(int str, int end){
    if(end-str==1)
        return x*bar[str]+z*bar[end];
    else if (end==str)
        return -900000000000000000;
    
    int mid = (str+end)/2;
    long long int fir = find(str, mid);
    long long int sec = find(mid+1, end);
    long long int front=x*bar[mid];
    long long int rear=z*bar[mid+1];
    for(int a=mid-1;a>=str;a--)
        if(pre(a, mid)>front)
            front = pre(a, mid);
    for(int a=mid+2;a<=end;a++)
        if(back(mid+1, a)>rear)
            rear = back(mid+1, a);
    // cout<<"now : fir = "<<fir<<" sec = "<<sec<<" front = "<<front<<" rear = "<<rear<<endl;
    return max(fir, max(sec, front+rear));
}

int main(){
    cin>>n>>x>>y>>z;
    for(int a=0;a<n;a++)
        scanf("%lld",&bar[a]);
    prefix[0] = bar[0];
    for(int a=1;a<n;a++)
        prefix[a] = prefix[a-1]+bar[a];
    cout<<find(0, n-1);

    return 0;
}