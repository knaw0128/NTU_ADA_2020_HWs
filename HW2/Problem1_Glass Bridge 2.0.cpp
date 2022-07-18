//ref:https://www.codeleading.com/article/50282799379/
#include<iostream>
#include<vector>
#include<math.h>
#define MY_MIN -99999999999999999
using namespace std;
int n,m,k;
int all;
long long int dp[500][500];
long long int input[500][500];
long long int BIT[800000];
int preBIT[800000];

int pre[500][500];
int stepx, stepy; //y  x
int preplace, findplace;

void translate(int r){
    stepy = (r-1)/m+1;
    stepx = (r-1)%m+1;
}

void init(){
    for(int a=0;a<=4*all;a++){
        BIT[a] = MY_MIN;
        preBIT[a] = -100;
    }
    for(int a=0;a<=n;a++)
        for(int b=0;b<=m;b++)
            pre[a][b] = -100;
}

int lowerbit(int i){
    return i&(-i);
}

void insert(int i, long long int val){
    int fir = i;
    while(i<=all){
        if(BIT[i]<val){
            BIT[i] = val;
            preBIT[i] = fir;
        }
        i+=lowerbit(i);
    }
}

long long int query(int l, int r){
    long long int ans = dp[(r-1)/m+1][(r-1)%m+1];
    findplace = r;
    while(l!=r){
        for(--r; r>=l+lowerbit(r);r-=lowerbit(r)){
            if(BIT[r]>ans){
                ans = BIT[r];
                findplace = preBIT[r];
            }
        }
        if(dp[(r-1)/m+1][(r-1)%m+1]>ans){
            ans = dp[(r-1)/m+1][(r-1)%m+1];
            findplace = r;
        }
    }
    return ans;
}   

long long int find_max(int y, int x){
    int now = (y-1)*m+x;
    int left = (y-1)*m+max(x-k, 1);
    int plus = x-k;

    long long int ans=MY_MIN;    preplace = -100;
    if(left<now){
        ans = query(left, now-1);
        preplace = findplace;
    }
    for(int a=0;a<k;a++){
        left -= m;
        now -= m;
        plus++;
        if(plus>1)
            left++;
        if(left<=0||now<=0||left>now)
            break;
        long long int next = query(left, now);
        if(next>ans){
            ans = next;
            preplace = findplace;
        }

    }
    return ans;
}

int main(){
    int t;
    string pass="Passable", unpass="Impassable";
    cin>>t;
    for(int a=0;a<t;a++){
        cin>>n>>m>>k;
        string tmp;
        all = n*m;

        init();

        for(int b=1;b<=n;b++){
            for(int c=1;c<=m;c++){
                cin>>tmp;
                if(tmp=="X")
                    input[b][c] = MY_MIN;
                else
                    input[b][c] = stoll(tmp);
            }
        }

        insert(1, input[1][1]);

        for(int b=1;b<=n;b++){
            for(int c=1;c<=m;c++){
                if(b==1&&c==1||input[b][c]==MY_MIN){
                    dp[b][c] = input[b][c];
                    continue;
                }
                long long int next = find_max(b, c);
                if(next==MY_MIN)
                    dp[b][c] = MY_MIN;
                else
                    dp[b][c] = input[b][c] + next;
                
                pre[b][c] = preplace;
                insert((b-1)*m+c, dp[b][c]);
            }
        }

        if(dp[n][m]!=MY_MIN)
            cout<<pass<<endl<<dp[n][m]<<endl;
        else{
            cout<<unpass<<endl;
            continue;
        }
        vector<int> path;
        int way = pre[n][m];
        while(way!=1){
            path.push_back(way);
            translate(way);
            way = pre[stepy][stepx];
        }
        path.push_back(1);
        cout<<path.size()+1<<endl;
        while(!path.empty()){
            translate(path.back());
            cout<<stepy<<" "<<stepx<<endl;
            path.pop_back();
        }
        cout<<n<<" "<<m<<endl;
    }

    return 0;
}