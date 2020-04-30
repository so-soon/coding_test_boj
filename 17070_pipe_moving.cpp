//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int N,res;
int board[16][16];

void dfs(int r, int c,int type);

int movement[3][3] = { {0,2,2} , {1,2,2} , {0,1,2}}; // [pipe type][move_num]

int cell[3][3][2] = { { {0,1},{0,1},{0,1} } ,  { {1,0},{1,0},{1,0} } , { {1,1},{0,1},{1,0} }}; // [move_num][cell_num][r,c]

int main(int argc, const char * argv[]) {
    res = 0;
    
    scanf("%d",&N);
    
    for (int i = 0 ; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d",&board[i][j]);
        }
    }
    dfs(0,1,0);
    
    printf("%d",res);
    
    return 0;
}

void dfs(int r, int c,int type){ //r ,c is tail
    int limit_move,limit_cell,tr,tc;
    bool isAble;
    if(r == N-1 && c == N-1){
        res++;
    }else{
        if (type == 2) limit_move = 3;
        else limit_move = 2;
        
        for(int mv = 0 ; mv < limit_move ; mv++){
            isAble = true;
            if(movement[type][mv] == 2) limit_cell = 3;
            else limit_cell = 1;
            for(int box = 0 ; box < limit_cell ; box++){
                tr = r + cell[ movement[type][mv] ][box][0];
                tc = c + cell[ movement[type][mv] ][box][1];
                
                if (tr >=N || tc >= N || board[tr][tc] == 1) {
                    isAble = false;
                }
                
            }
            if(isAble){
                dfs(r+ cell[ movement[type][mv] ][0][0], c + cell[ movement[type][mv] ][0][1], movement[type][mv]);
            }
            
        }
        
    }
    
}
