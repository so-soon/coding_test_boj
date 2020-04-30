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
#include <string.h>
#include <vector>
#include <set>

using namespace std;

int N,M,K;
int a[60][60];
int temp_a[60][60];
int origin_a[60][60];
int combi[6];

vector< vector<int> > order;
bool isused[6];
set<int> res;

void rotation(int r,int c,int s);
void dfs(int depth);
void calc(void);

int main(int argc, const char * argv[]) {
    vector<int> temp;
    int tr,tc,ts;
    scanf("%d %d %d",&N,&M,&K);
    
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1 ; j <= M; j++){
            scanf("%d",&origin_a[i][j]);
            
        }
    }
    
    for(int i = 0 ; i < K;i++) isused[i] = false;
    
    for(int nk = 0; nk < K ; nk++){
        temp.clear();
        scanf("%d %d %d",&tr,&tc,&ts);
        temp.push_back(tr);
        temp.push_back(tc);
        temp.push_back(ts);
        order.push_back(temp);
        
        
    }
    
    
    dfs(0);
    
    printf("%d",*(res.begin()));
    
    return 0;
}

void rotation(int r,int c,int s){
    int dir[4][2] = { {0,1} , {1,0} , {0,-1} , {-1,0} };
    int tr,tc;
    tr = r-s;
    tc = c-s;
    
    for(int i = 0 ; i < 4 ; i++){
        for(int b = 0 ; b < (s*2) ; b++){
            /*if (b == (s*2)-1 ) { //edge (tr == r-s && tc == c+s) || (tr == r+s && tc == c+s) || (tr == r+s && tc == c-s) || (tr == r-s && tc == c-s)
                temp_a[tr+dir[(i+1)%4][0]][tc+dir[(i+1)%4][1]] = a[tr][ tc ];
                tr +=dir[(i+1)%4][0];
                tc +=dir[(i+1)%4][1];
            }*/
            
            
            temp_a[tr+dir[i][0]][tc+dir[i][1]] = a[tr][tc];
            tr += dir[i][0];
            tc += dir[i][1];
            
        }
        
    }
    
    
}

void dfs(int depth){
    if(depth == K){
        for(int i = 1 ; i <= N ; i++){
            for(int j = 1 ; j <= M; j++){
                a[i][j] = origin_a[i][j];
                
            }
        }
        memset(temp_a,0,sizeof(temp_a));
        
        for(int i = 0 ; i < K; i++){ //combi i
            for(int ts = 1 ; ts <= order[ combi[i] ][2] ; ts++){
                rotation(order[ combi[i] ][0], order[ combi[i] ][1], ts);
                for(int i = 1 ; i <= N ; i++){
                    for(int j = 1 ; j <= M; j++){
                        if(temp_a[i][j] != 0) a[i][j] = temp_a[i][j];
                    }
                }
                
                /*printf("\n");
                printf("\n");
                for(int r = 1 ; r <=N ; r++){
                    for(int c = 1 ; c <= M ; c++){
                        printf("%d ",a[r][c]);
                    }
                printf("\n");
                }*/
            }
            
        }
        calc();
        
    }else{
        for(int i = 0 ; i < K ; i++){
            if(isused[i]) continue;
            
            isused[i] = true;
            combi[depth] = i;
            dfs(depth+1);
            isused[i] = false;
        }
    }
    
}
void calc(void){
    set<int> sum_row;
    int temp_sum = 0;
    for(int r = 1 ; r <=N ; r++){
        temp_sum = 0;
        for(int c = 1 ; c <= M ; c++){
            temp_sum += a[r][c];
        }
        sum_row.insert(temp_sum);
    }
    /*printf("\n");
    printf("\n");
    for(int r = 1 ; r <=N ; r++){
        for(int c = 1 ; c <= M ; c++){
            printf("%d ",a[r][c]);
        }
        printf("\n");
    }*/
    res.insert(*(sum_row.begin()));
}
