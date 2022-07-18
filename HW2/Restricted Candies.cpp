#include<iostream>
#include<deque>
#include<algorithm>
#include<set>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

long long int maximum[1000009];

struct lar{
    long long int val;
    long long int big;
    long long int pos1;
    long long int pos2;
};

class node{
public:
    vector<long long int> candy;
    multiset<lar> tree;
    int lft[100009];
    int rgh[100009];
    int head;
    int tail;
    int find_left(int pos){
        if(candy[lft[pos]]!=0)
            return lft[pos];
        return lft[pos] = find_left(lft[pos]);
    }
    int find_right(int pos){
        if(candy[rgh[pos]]!=0)
            return rgh[pos];
        return rgh[pos] = find_right(rgh[pos]);
    }
    void init(deque<long long int> tar){
        tree.clear();
        int len = tar.size();
        for(int a=0;a<len;a++)
            candy.push_back(tar[a]);
        head = tar.front();
        tail = tar.back();
        for(int a=0;a<len;a++){
            lft[a] = (a-1+len)%len;
            rgh[a] = (a+1)%len;

            lar tmp;
            tmp.pos1 = a;
            tmp.pos2 = (a+1)%len;
            tmp.val = tar[tmp.pos1] + tar[tmp.pos2];
            tmp.big = max(tar[tmp.pos1], tar[tmp.pos2]);

            tree.insert(tmp);
        }
    }
};

bool const operator<(const lar a, const lar b){
    return tie(a.val,a.big,a.pos1,a.pos2)<tie(b.val,b.big,b.pos1,b.pos2);
}

void show(int n){
    for(int a=1;a<=n;a++)
        cout<<maximum[a]<<" ";
    cout<<endl;
}

int main(){
    int flag, t;
    cin>>t>>flag;
    int n;
    for(int i=0;i<t;i++){
        cin>>n;
        for(int a=1;a<=n;a++)
            maximum[a] = 0;
        long long int tmp;
        int remain = n;
        long long int all = 0;
        
        deque<long long int> list;
        for(int a=0;a<n;a++){
            cin>>tmp;
            if(list.empty()||tmp*list.back()<0){
                list.push_back(tmp);
                all+=tmp;
            }
            else if(list.back()<tmp){
                all = all-list.back()+tmp;
                list[list.size()-1] = tmp;
                remain--;
            }
            else
                remain--;
        }
        
        node prelist[2];
        prelist[0].init(list);
        maximum[remain--] = all;

        if(remain>0){
            if(all-list.front() > all-list.back()){
                maximum[remain--] = all-list.front();
                list.pop_front();
            }
            else{
                maximum[remain--] = all-list.back();
                list.pop_back();
            }
        }
        else{
            show(n);
            continue;
        }

        prelist[1].init(list);
        int pre = 1;

        for(int a=remain;a>0;a--){
            int pre2 = 1-pre;
            lar now = *(prelist[pre2].tree.begin());
            int now1 = now.pos1;
            int now2 = now.pos2;
            
            maximum[a] = maximum[a+2]-now.val;

            int left = prelist[pre2].find_left(now1);
            int right = prelist[pre2].find_right(now2);
            int posbye[3] = {left, now1, now2};

            for(int b=0;b<3;b++){
                lar tmp;
                tmp.pos1 = posbye[b];
                tmp.pos2 = prelist[pre2].find_right(posbye[b]);
                tmp.val = prelist[pre2].candy[tmp.pos1] + prelist[pre2].candy[tmp.pos2];
                tmp.big = max(prelist[pre2].candy[tmp.pos1], prelist[pre2].candy[tmp.pos2]);
                prelist[pre2].tree.erase(tmp);
            }
            lar tmp2;
            tmp2.pos1 = left;
            tmp2.pos2 = right;
            tmp2.val = prelist[pre2].candy[tmp2.pos1] + prelist[pre2].candy[tmp2.pos2];
            tmp2.big = max(prelist[pre2].candy[tmp2.pos1], prelist[pre2].candy[tmp2.pos2]);
            prelist[pre2].tree.insert(tmp2);

            prelist[pre2].rgh[left] = right;
            prelist[pre2].lft[right] = left;

            prelist[pre2].candy[now1] = 0;
            prelist[pre2].candy[now2] = 0;

            pre = 1-pre;

        }

        show(n);
    
    }
    return 0;
}