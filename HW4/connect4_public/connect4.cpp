#include <vector>
#include <algorithm>
#include "connect4.h"
using namespace std;
#define INF 9999999999999 

int board[8][7];
int height[7],moves;
int maxdepth;

int next_step();
long long int get_score(int cur_move,int player, long long int alpha, long long int beta);
int check_win(int k);
long long int final_score(int who);

// The columns are numbered from 0 to 6
int decide(int yp_move) { //0 for me 1 for other
    if (yp_move == -1) {
        // A new game starts
        // TODO: Please remember to reset everything here (if needed)
        for(int a=0;a<7;a++){
            for(int b=0;b<6;b++)
                board[a][b]=-1;
            height[a]=0;
        }
        moves=1;
        maxdepth=5;
        board[3][height[3]++]=0;
        return 3;
    }
    else{
        board[yp_move][height[yp_move]++]=1;
    }
    
    int ans=next_step();
    board[ans][height[ans]++]=0;
    moves+=2;
    // if(moves==7)
    //     maxdepth++;

    if(moves>=21)
        maxdepth=100;
    // if(moves==7)
    //     sleep(3);
    return ans;
}

int next_step(){
    long long int max_score=-INF,ret=7;
    for(int a=0;a<7;a++){
        if(height[a]>=6)
            continue;
        board[a][height[a]++]=0;
        if(check_win(0)){
            board[a][--height[a]]=-1;
            return a;
        }
        long long int now=-get_score(moves+1,1,-INF,INF);
        board[a][--height[a]]=-1;
        if(now>=max_score){
            max_score=now;
            ret=a;
        }
    }
    return ret;
}

int check_win(int who){
    for(int a=0;a<7;a++){
        for(int b=0;b<3;b++){
            if(board[a][b]==who&&board[a][b+1]==who&&board[a][b+2]==who&&board[a][b+3]==who)
                return 1;
            if(a<4&&board[a][b]==who&&board[a+1][b+1]==who&&board[a+2][b+2]==who&&board[a+3][b+3]==who)
                return 1;
            if(a>2&&board[a][b]==who&&board[a-1][b+1]==who&&board[a-2][b+2]==who&&board[a-3][b+3]==who)
                return 1;     
        }
    }
    for(int b=0;b<6;b++){
        for(int a=0;a<4;a++){
            if(board[a][b]==who&&board[a+1][b]==who&&board[a+2][b]==who&&board[a+3][b]==who)
                return 1;
        }
    }
    return 0;
}

long long int get_score(int cur_move,int player, long long int alpha, long long int beta){
    int can=0;
    for(int a=0;a<7;a++){
        if(height[a]>=6){
            can++;continue;
        }
        board[a][height[a]++]=player;
        if(check_win(player)){
            board[a][--height[a]]=-1;
            return INF;
        }
        board[a][--height[a]]=-1; 
    }
    if(can==7)
        return 0;

    if(cur_move-moves>maxdepth)
        return final_score(player);

    for(int a=0;a<7;a++){
        if(height[a]>=6) continue;
        board[a][height[a]++]=player;
        long long int score = -get_score(cur_move+1,1-player,-beta,-alpha);
        board[a][--height[a]]=-1;
        if(score>=beta)
            return score;
        alpha=max(score,alpha);
    }
    return alpha;
}

long long int final_score(int who){
    long long int score=0;
    int oppo=1-who;
    // for(int a=0;a<height[3];a++)
    //     if(board[3][a]==who)
    //         score+=3;
    
    for(int a=0;a<7;a++){
        for(int b=0;b<3;b++){
            int me=0,no=0,op=0;
            for(int c=0;c<4;c++){
                if(board[a][b+c]==who)
                    me++;
                else if(board[a][b+c]==oppo)
                    op++;
                else
                    no++;
            }
            if(me==3&&no==1)
                score+=9;
            else if(me==2&&no==2)
                score+=4;
            else if(me==1&&no==3)
                score+=1;
            else if(op==3&&no==1)
                score-=4;
            else if(op==2&&no==2)
                score-=3;
            else if(op==1&&no==3)
                score-=1;
        }
    }
    for(int a=0;a<6;a++){
        for(int b=0;b<4;b++){
            int me=0,no=0,op=0;
            for(int c=0;c<4;c++){
                if(board[b+c][a+c]==who)
                    me++;
                else if(board[b+c][a+c]==oppo)
                    op++;
                else
                    no++;
            }
            if(me==3&&no==1)
                score+=9;
            else if(me==2&&no==2)
                score+=4;
            else if(me==1&&no==3)
                score+=1;
            else if(op==3&&no==1)
                score-=4;
            else if(op==2&&no==2)
                score-=3;
            else if(op==1&&no==3)
                score-=1;
        }
    }
    for(int a=0;a<4;a++){
        for(int b=0;b<3;b++){
            int me=0,no=0,op=0;
            for(int c=0;c<4;c++){
                if(board[a+c][b+c]==who)
                    me++;
                else if(board[a+c][b+c]==oppo)
                    op++;
                else
                    no++;
            }
            if(me==3&&no==1)
                score+=9;
            else if(me==2&&no==2)
                score+=4;
            else if(me==1&&no==3)
                score+=1;
            else if(op==3&&no==1)
                score-=4;
            else if(op==2&&no==2)
                score-=3;
            else if(op==1&&no==3)
                score-=1;
        }
    }//----
    for(int a=3;a<7;a++){
        for(int b=0;b<3;b++){
            int me=0,no=0,op=0;
            for(int c=0;c<4;c++){
                if(board[a-c][b+c]==who)
                    me++;
                else if(board[a-c][b+c]==oppo)
                    op++;
                else
                    no++;
            }
            if(me==3&&no==1)
                score+=9;
            else if(me==2&&no==2)
                score+=4;
            else if(me==1&&no==3)
                score+=1;
            else if(op==3&&no==1)
                score-=4;
            else if(op==2&&no==2)
                score-=3;
            else if(op==1&&no==3)
                score-=1;
        }
    }

    return score;
}

