#include<iostream>
#include<bits/stdc++.h>
using namespace std;
long long int dp[600][600];
long long int gcds[600][600];

int main(){
    int n;
    long long int nums[600];
    cin>>n;
    for(int a=0;a<n;a++)
        cin>>nums[a];
    
    for(int a=0;a<n;a++)
        for(int b=0;b<n;b++){
            if(a!=b)
                gcds[a][b] = __gcd(nums[a], nums[b]); 
            else
                gcds[a][b] = -1;
        }
            
    for(int a=0;a<n;a++)
        dp[a][a] = -1;
        
    
    for(int k=1;k<n;k++){
        for(int left=0;left<n-k;left++){
            int right = left+k;

            if(gcds[left][right]>1&&dp[left+1][right-1]>=0)
                dp[left][right] = dp[left+1][right-1]+gcds[left][right];
            else
                dp[left][right] = -1;

            for(int j=left+1;j<right;j++){
                if(gcds[left][j]>1&&gcds[j][right]>1&&gcds[left][right]>1&&dp[left+1][j-1]>=0&&dp[j+1][right-1]>=0)
                    dp[left][right] = max(dp[left][right], dp[left+1][j-1]+dp[j+1][right-1]+gcds[left][j]+gcds[j][right]);

                if(dp[left][j]>=0&&dp[j+1][right]>=0)
                    dp[left][right] = max(dp[left][right], dp[left][j]+dp[j+1][right]);
            }
        }
    }    

    if(dp[0][n-1]>0)
        cout<<dp[0][n-1];
    else
        cout<<"-1";
    return 0;
}