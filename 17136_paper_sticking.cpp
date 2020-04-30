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
#include <list>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int board[10][10];
int original_board[10][10];
vector<pair<int,int> > pos_1;

int tot_num_1;
set<int> res;

void dfs(int n1,int n2,int n3,int n4,int n5,int remain,int temp_board[][10]);

int main(int argc, const char * argv[]) {
    
    tot_num_1 = 0;
    
    
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < 10 ; j++){
            scanf("%d",&board[i][j]);
            original_board[i][j] = board[i][j];
            if(board[i][j] == 1){
                pos_1.push_back(pair<int,int>(i,j) );
                tot_num_1++;
            }
            
        }
    }
    
    dfs(5, 5, 5, 5, 5, tot_num_1,board);
    if (res.empty()) {
        printf("%d",-1);
    }
    else printf("%d",*(res.begin()));
    return 0;
}
void dfs(int n1,int n2,int n3,int n4,int n5,int remain,int temp_board[][10]){
    
    int temp[10][10];
    vector<pair<int, int> >::iterator iter;
    bool isFail = false;
    
    if (remain == 0) {
        res.insert((5-n1)+(5-n2)+(5-n3)+(5-n4)+(5-n5));
        return;
    }
    else if(remain<0) return;
    
    
    for(iter = pos_1.begin(); iter!=pos_1.end();++iter){
        if(temp_board[(*iter).first][(*iter).second] == 1) break;
    }
    
    if (iter == pos_1.end()) {
        if (remain == 0) {
            res.insert((5-n1)+(5-n2)+(5-n3)+(5-n4)+(5-n5));
        }
        return;
    }

    for (int r = 0 ; r < 10 ; r++) {
        for(int c = 0 ; c < 10; c++) temp[r][c] = temp_board[r][c];
    }
    
    for(int i = 5 ; i >= 1 ; i--){
        if (i == 1 && n1 <= 0) continue;
        if (i == 2 && n2 <= 0) continue;
        if (i == 3 && n3 <= 0) continue;
        if (i == 4 && n4 <= 0) continue;
        if (i == 5 && n5 <= 0) continue;
        
        isFail = false;
        //attch to board
        
        
        for(int r = (*iter).first ; r<(*iter).first+i ; r++){
            if(isFail){
                break;
            }
            for(int c = (*iter).second ; c<(*iter).second+i; c++){
                if(r >=10 || c>=10)
                {
                    isFail = true;
                    break;
                }
                if(temp[r][c] == 1) temp[r][c] = 2;
                else{
                    isFail = true;
                    break;
                }
                
            }
            
        }
        if (isFail){
            for (int r = 0 ; r < 10 ; r++) {
                for(int c = 0 ; c < 10; c++) temp[r][c] = temp_board[r][c];
            }
            continue;
        }
        
        
        //dfs
        if (i == 1) dfs(n1-1, n2, n3, n4, n5, remain-1,temp);
        if (i == 2) dfs(n1, n2-1, n3, n4, n5, remain-4,temp);
        if (i == 3) dfs(n1, n2, n3-1, n4, n5, remain-9,temp);
        if (i == 4) dfs(n1, n2, n3, n4-1, n5, remain-16,temp);
        if (i == 5) dfs(n1, n2, n3, n4, n5-1, remain-25,temp);
        
        //erase
        
        for (int r = 0 ; r < 10 ; r++) {
            for(int c = 0 ; c < 10; c++) temp[r][c] = temp_board[r][c];
        }

        
        
    }
    
    
    
}
