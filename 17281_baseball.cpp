//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <deque>
using namespace std;

int N;
int score[50][9];

int combi[9];
set<int> res;
bool player[9];

void dfs(int depth);
void play(void);

int main(int argc, const char * argv[]) {
    combi[3] = 1;
    
    scanf("%d",&N);
    
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < 9 ; j++){
            scanf("%d",&score[i][j]);
        }
    }
    
    for(int i = 0; i < 9 ; i++) player[i] = false;
    dfs(0);
    
    printf("%d",*(--res.end()));
    
    return 0;
}

void dfs(int depth){
    if(depth == 9 ) play();
    else if(depth == 3) dfs(depth+1);
    else {
        for(int i = 2; i <=9 ; i++){
            if (player[i]) {
                continue;
            }
            combi[depth] = i;
            player[i] = true;
            dfs(depth+1);
            player[i] = false;
        }
    }
    
}

void play(void){
    deque<int> mound;
    int now_player = 0;
    int out_count;
    int tot_score = 0;
    int step;
    int in_player;
    for(int en = 0 ; en < N ; en++){
        out_count = 0;
        mound.clear();
        
        while (out_count < 3) {
            in_player = 0;
            if (score[en][combi[now_player%9]-1] == 0) {
                out_count++;
                now_player++;
                continue;
            }
            else if( score[en][combi[now_player%9]-1] == 4){
                tot_score += mound.size()+1;
                mound.clear();
            }
            else{
                step = score[en][combi[now_player%9]-1];
                
                for (deque<int>::iterator iter = mound.begin(); iter != mound.end(); ++iter) {
                    (*iter)+=step;
                    if((*iter) > 3){
                        tot_score++;
                        in_player++;
                    }
                }
                mound.push_back(score[en][combi[now_player%9]-1]);
                for(int i = 0 ; i < in_player; i++) mound.pop_front();
            }

            now_player++;
            
        }
    }
    res.insert(tot_score);
    
}
