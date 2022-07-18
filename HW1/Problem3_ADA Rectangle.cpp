#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int, int>> place;
inline int Xcmp(pair<int, int>& a, pair<int , int>& b){
    return a.first<b.first;
}
inline int Ycmp(pair<int, int>& a, pair<int , int>& b){
    return a.second<b.second;
}

long long int BS(vector<pair<int, int>>& now, int tmp){
    int l=0, r=now.size()-1, mid;
    long long int ans = now.size();
    while (r>=l){
        mid = (r+l)/2;
        if(tmp>now[mid].second){
            ans -= mid-l+1;
            l = mid+1;
        }
        else
            r = mid-1;
    }
    return ans;
}

long long int find_ans(int l, int r){
    if(r-l==1)
        return 1;
    if(r==l)
        return 0;
    int mid = (r+l)/2;
    long long int ans = find_ans(l, mid)+find_ans(mid+1, r);
    vector<pair<int, int>> left;
    vector<pair<int, int>> right;
    for(int a=l;a<=mid;a++)
        left.push_back(place[a]);
    for(int a=mid+1;a<=r;a++)
        right.push_back(place[a]);
    sort(left.begin(), left.end(), Ycmp);       //pop left
    sort(right.begin(), right.end(), Ycmp);     //pop right
    int idxl=0, idxr=0;
    vector<pair<int, int>> le;
    vector<pair<int, int>> ri;

    while(idxl<left.size()||idxr<right.size()){
        if(idxl<left.size()&&(idxr==right.size()||left[idxl].second<right[idxr].second)){
            pair<int, int> now = left[idxl++];
            while(le.size()>0&&le.back().first<now.first)
                le.pop_back();
            int tar;
            if(!le.empty())
                tar = le.back().second;
            else{
                le.emplace_back(now);
                ans += ri.size();
                continue;
            }
            le.emplace_back(now);
            ans += BS(ri, tar);
        }
        else{
            pair<int, int> now = right[idxr++];
            while(ri.size()>0&&ri.back().first>now.first)
                ri.pop_back();
            int tar;
            if(!ri.empty())
                tar = ri.back().second;
            else{
                ri.emplace_back(now);
                ans += le.size();
                continue;
            }
            ri.emplace_back(now);
            ans += BS(le, tar);
        }
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    for(int a=0;a<n;a++){
        pair<int, int> tmp;
        cin>>tmp.first>>tmp.second; //x  y
        place.emplace_back(tmp);
    }
    sort(place.begin(), place.end(), Xcmp);
    cout<<find_ans(0, n-1);
    return 0;
}