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


deque<int> tree[11][11];
int N,M,K;
int A[11][11];
int board[11][11];

int main(int argc, const char * argv[]) {
    int cx,cy,age,year;
    
    deque<int>::iterator iter;
    int x[8] = {-1,-1,-1,0,0,1,1,1};
    int y[8] = {-1,0,1,-1,1,-1,0,1};
    
    year = 0;
    
    scanf("%d %d %d",&N,&M,&K);
   
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1 ; j <= N ; j++){
            scanf("%d",&A[i][j]);
            board[i][j] = 5;
        }
    }
    
    for(int i = 0 ; i < M ; i++){
        scanf("%d %d %d",&cx,&cy,&age);
        tree[cx][cy].push_front(age);
    }
    
    while(year < K){
         //spring
           for(int r = 1 ; r <= N ; r++){
               for(int c = 1 ; c <= N; c++){
                   for(iter = tree[r][c].begin() ; iter != tree[r][c].end() ; ++iter){
                       if((board[r][c] >= (*iter)) && ((*iter) != 0)){
                           board[r][c] -= (*iter);
                           (*iter)++;
                       }
                       else if(((*iter) != 0)){ //die ( -age means a dead tree, 0 means not exist
                           (*iter) = -(*iter);
                           M--;
                       }
                       else if((*iter) == 0) break;
                   }
               }
           }
           
           
           //summer
           for(int r = 1 ; r <= N ; r++){
               for(int c = 1 ; c <= N; c++){
                   for(iter = tree[r][c].begin() ; iter != tree[r][c].end() ; iter++){
                       if((*iter) < 0){
                           board[r][c] += (-(*iter))/2;
                           (*iter) = 0;
                       }
                       else if((*iter) == 0) break;
                   }
               }
           }
           
           //fall
           for(int r = 1 ; r <= N ; r++){
               for(int c = 1 ; c <= N; c++){
                   for(iter = tree[r][c].begin() ; iter != tree[r][c].end() ; iter++){
                       if((*iter)%5 == 0 && (*iter)!= 0){
                           for(int a = 0; a < 8; a++){
                               if((r+x[a]) > 0 && (r+x[a]) <= N && (c+y[a]) > 0 && (c+y[a]) <= N){
                                   tree[r+x[a]][c+y[a]].push_front(1);
                                   M++;
                               }
                           }
                       }
                       else if((*iter) == 0) break;
                   }
               }
           }
           //winter
           for(int r = 1 ; r <= N ; r++){
               for(int c = 1 ; c <= N; c++){
                   board[r][c] += A[r][c];
               }
           }
           
        year++;
    }
    
    printf("%d",M);
    
    return 0;
}
