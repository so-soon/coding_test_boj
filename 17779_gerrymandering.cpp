//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <utility>
#include <string.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

vector<pair<int,int> > v;
vector<pair<int,int> > active;
set<int> res;

int N,M,remain;
int board[50][50];
int temp[50][50];
void dfs(int depth,int num);

int main(int argc, const char * argv[]) {
    
    
    remain = 0;
    
    scanf("%d %d",&N,&M);
    
    for(int r = 0 ; r < N ; r++){
        for(int c = 0 ; c < N ; c++) {
            scanf("%d",&board[r][c]);
            if (board[r][c] == 0) remain++;
            else if(board[r][c] == 2) v.push_back(pair<int,int>(r,c));
        }
    }
    
    dfs(0,0);
    
    if(res.size() == 0 ) printf("-1");
    else printf("%d",*(res.begin()));
    return 0;
}

void dfs(int depth,int num){ // depth : number of activated virus
    int r,t = 0,row,col;
    queue<pair<int,int> > q;
    if (depth >= M) { // spread virus
        r = remain;
        
        for (int i = 0 ; i < N; i++) {
            for(int j = 0 ;  j < N ; j++) temp[i][j] = board[i][j];
        }
        
        for (int i = 0; i < active.size(); i++) {
            q.push(pair<int, int>(active[i].first,active[i].second));
        }
        
        //printf("\n-------------------------------------\n");
        while(!(q.empty()) && r > 0){ //whole loop
            
            for(int co = int(q.size())-1 ; co >= 0  ; co--){
                row = q.front().first;
                col = q.front().second;
                q.pop();
                
                temp[row][col] = 3;
                
                if (row + 1 < N && (temp[row+1][col] == 0 || temp[row+1][col] == 2)) { // down
                    if(temp[row+1][col] == 0) r--;
                    temp[row+1][col] = 3;
                    q.push(pair<int, int>(row+1,col));
                }
                
                if (row - 1 >= 0  && (temp[row-1][col] == 0 || temp[row-1][col] == 2)) { // up
                    
                    if(temp[row-1][col] == 0) r--;
                    temp[row-1][col] = 3;
                    q.push(pair<int, int>(row-1,col));
                }
                
                if (col + 1 < N  && (temp[row][col+1] == 0 || temp[row][col+1] == 2)) { // right
                    
                    if(temp[row][col+1] == 0) r--;
                    temp[row][col+1] = 3;
                    q.push(pair<int, int>(row,col+1));
                }
                
                if (col - 1 >= 0  && (temp[row][col-1] == 0 || temp[row][col-1] == 2)) { // left
                    
                    if(temp[row][col-1] == 0) r--;
                    temp[row][col-1] = 3;
                    q.push(pair<int, int>(row,col-1));
                }
                
                
            }
            /*
            printf("\n");
            for(int a = 0 ; a < N ; a ++){
                for(int b=  0; b < N ; b++) printf("%d ",temp[a][b]);
                printf("\n");
            }*/
            t++;
        }
        if (r == 0) {
            res.insert(t);
        }
        
    } else { //combination
        for(int i = num; i < v.size() ; i++){
            if (depth < active.size()) { //already exist
                active[depth] = pair<int,int>(v[i].first,v[i].second);
            }
            else{ // depth >= active size
                active.push_back(pair<int,int>(v[i].first,v[i].second));
            }
            
            dfs(depth+1,i+1);
        }
    }
    
    return;
}
