//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <set>
#include <deque>
#include <queue>
#include <utility>
#include <string.h>

using namespace std;


int shark[10001][5]; // r,c,s,d,z
set<int> sa[100];

int main(int argc, const char * argv[]) {

    int R,C,M,sr,sc,s,d,z,res,t_dir;
    
    
    int dir[4][2] = {{-1,0},{1,0},{0,1},{0,-1}}; // 위 아래 오른 왼
    set<int>::iterator iter;
    int board[100][100];
    int temp_board[100][100];
    memset(board,0,sizeof(board));
    res = 0;
    
    scanf("%d %d %d",&R,&C,&M);
    
    for(int i = 1 ; i <= M ; i++){
        scanf("%d %d %d %d %d",&sr,&sc,&s,&d,&z);
        shark[i][0] = sr-1;
        shark[i][1] = sc-1;
        shark[i][2] = s;
        shark[i][3] = d-1;
        shark[i][4] = z;
        board[sr-1][sc-1] = i;
        sa[sc-1].insert(sr-1);
    }
    
    
    for(int i = 0 ; i < C ; i++){ // main loop
        
        if(!sa[i].empty()){ // available fishing column
            res+= shark[board[(*(sa[i].begin()))][i]][4];
            board[(*(sa[i].begin()))][i] = 0;
            sa[i].erase(sa[i].begin());
        }
        /*
        for(int row = 0 ; row < R ; row++){
            if (board[row][i] != 0 ) {
                res += shark[board[row][i]][4];
                board[row][i] = 0;
                break;
            }
        }
        */
        memset(temp_board,0,sizeof(temp_board));
        
        
        for(int col = 0 ; col < C ; col++){ //moving loop
            if(!sa[col].empty()){
                for(iter = sa[col].begin() ; iter != sa[col].end(); ++iter){ // each row, iter == row
                    sr = *(iter);
                    sc = col;
                    t_dir = shark[board[*(iter)][col]][3];
                    if(t_dir == 0 || t_dir == 1){
                        shark[board[*(iter)][col]][2] %= (2*R)-2;
                    }
                    else{
                        shark[board[*(iter)][col]][2] %= (2*C)-2;
                    }
                    for(int move = 0; move < shark[board[*(iter)][col]][2] ; move++){ //move start
                        if((sr+dir[t_dir][0]) < 0 || (sr+dir[t_dir][0]) >= R || (sc+dir[t_dir][1]) < 0 || (sc+dir[t_dir][1]) >= C){ // outside
                            if(shark[board[*(iter)][col]][3] % 2 == 0){
                                shark[board[*(iter)][col]][3] += 1;
                            }
                            else shark[board[*(iter)][col]][3] -= 1;
                        }
                        t_dir = shark[board[*(iter)][col]][3];
                        
                        sr += dir[t_dir][0];
                        sc += dir[t_dir][1];
                    } //move over
                    if(temp_board[sr][sc] != 0){ //battle shark
                        if (shark[board[*(iter)][col]][4] > shark[temp_board[sr][sc]][4]) { //new shark win
                            temp_board[sr][sc] = board[*(iter)][col];
                        }
                    }
                    else{ //peace
                        temp_board[sr][sc] = board[*(iter)][col];
                    }
                }
            }
        }
        
        
        /*
        for(int a = 0 ; a < C ; a++){
            for(int b = 0 ; b < R ; b++){
                if(board[b][a]!=0){
                    sr = b;
                    sc = a;
                    t_dir = shark[board[sr][sc]][3];
                    for(int move = 0; move < shark[board[b][a]][2] ; move++){ //move start
                        if((sr+dir[t_dir][0]) < 0 || (sr+dir[t_dir][0]) >= R || (sc+dir[t_dir][1]) < 0 || (sc+dir[t_dir][1]) >= C){ // outside
                            if(shark[board[b][a]][3] % 2 == 0){
                                shark[board[b][a]][3] += 1;
                            }
                            else shark[board[b][a]][3] -= 1;
                        }
                        t_dir = shark[board[b][a]][3];
                        
                        sr += dir[t_dir][0];
                        sc += dir[t_dir][1];
                    } //move over
                    if(temp_board[sr][sc] != 0){ //battle shark
                        if (shark[board[b][a]][4] > shark[temp_board[sr][sc]][4]) { //new shark win
                            temp_board[sr][sc] = board[b][a];
                        }
                    }
                    else{ //peace
                        temp_board[sr][sc] = board[b][a];
                    }
                }
            }
        }
         */
        
        for(int a = 0 ; a < C ; a++){
            sa[a].clear();
            for(int b = 0; b < R; b++){
                if(temp_board[b][a] != 0) sa[a].insert(b);
                board[b][a] = temp_board[b][a];
            }
        }
        /*
        for(int a = 0 ; a < C ; a++){
        for(int b = 0; b < R; b++){
            board[b][a] = temp_board[b][a];
            }
            
        }*/
        
    }
    
    printf("%d",res);
    return 0;
}
