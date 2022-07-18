#include "ada-hw4-p3.h"
#include <set>
#include <map>
using namespace std;

vector<int> contest;
set<int> inside;
map<int, int> with;
vector<int> ret;

vector<int> init(int N) {
    contest.resize(N);
    inside.insert(-1);
    for (int i=0;i<N;++i){
        contest[i]=i;
        inside.insert(i);
    }
    
    int pre=0;
    for(int a=1;a<N;a++){
        if(pre==-1){
            pre=a;
            continue;
        }
        if(!compare(pre,a)){
            inside.erase(pre);
            inside.erase(a);
            with[pre]=a;
            with[a]=pre;
            ret.push_back(pre);
            ret.push_back(a);
            pre=*(--inside.lower_bound(pre));
        }
        else{
            pre=a;
        }

    }
    return ret;
}

vector<int> insert(int p, int id) {
    contest.insert(contest.begin()+p,id);
    int left=p,right=p;
    while(left>=0&&inside.find(contest[left])==inside.end())
        left--;
    while(right<contest.size()&&inside.find(contest[right])==inside.end())
        right++;
        
    if(left>=0&&!compare(contest[left],id)){
        inside.erase(contest[left]);
        inside.erase(id);
        with[id]=contest[left];
        with[contest[left]]=id;
        ret.push_back(contest[left]);
        ret.push_back(id);
    }
    else if(right<contest.size()&&!compare(id,contest[right])){
        inside.erase(contest[right]);
        inside.erase(id);
        with[id]=contest[right];
        with[contest[right]]=id;
        ret.push_back(contest[right]);
        ret.push_back(id);
    }
    else
        inside.insert(id);

    return ret;
}

vector<int> remove(int p) {
    int id=contest[p];
    contest.erase(contest.begin()+p);

    if(inside.find(id)!=inside.end()){
        inside.erase(id);
    }
    else{
        int frd=with[id];
        with.erase(frd);with.erase(id);
        inside.insert(frd);
        int place=-1;
        for(int a=0;a<ret.size();a++)
            if(ret[a]==id)
                ret.erase(ret.begin()+a);
        for(int a=0;a<ret.size();a++)
            if(ret[a]==frd)
                ret.erase(ret.begin()+a);
        
        for(int a=0;a<contest.size();a++){
            if(contest[a]==frd){
                place=a;
            }
        }

        int left=place-1,right=place+1;
        while(left>=0&&inside.find(contest[left])==inside.end())
            left--;
        while(right<contest.size()&&inside.find(contest[right])==inside.end())
            right++;

        if(left>=0&&!compare(contest[left],frd)){
            inside.erase(contest[left]);
            inside.erase(frd);
            with[frd]=contest[left];
            with[contest[left]]=frd;
            ret.push_back(contest[left]);
            ret.push_back(frd);
        }
        else if(right<contest.size()&&!compare(frd,contest[right])){
            inside.erase(contest[right]);
            inside.erase(frd);
            with[frd]=contest[right];
            with[contest[right]]=frd;
            ret.push_back(contest[right]);
            ret.push_back(frd);
        }
    }
    
    return ret;
}
