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



int main(int argc, const char * argv[]) {
    int N,sr,sc,originr = 0,originc = 0,t,size,sco,temp_r,temp_c,temp_d,tco,d;
    int pool[20][20];
    int dir[4][2] = {{-1,0},{0,-1},{0,1},{1,0}};
    int visited[20][20];
    bool isEatFishes = false;
    
    queue<pair<int,int>> q;
    queue<int> depth;
    
    t = 0;
    size = 2;
    sco = 2;
    tco = 0;
    
    scanf("%d",&N);
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++){
            scanf("%d",&pool[i][j]);
            if(pool[i][j] == 9){
                sr = i;
                sc = j;
                originr = i;
                originc = j;
            }
        }
    }
    
    do{
        d = 0;
        q = queue<pair<int,int>>();
        depth = queue<int>();
        q.push(pair<int,int>(originr,originc));
        depth.push(d);
        isEatFishes = false;
        memset(visited,0,sizeof(visited));
        temp_r = 21;
        temp_c = 21;
        temp_d = 10000000;
        
        visited[originr][originc] = 1;
        while(!(q.empty())){
            sr = q.front().first;
            sc = q.front().second;
            d = depth.front();
            q.pop();
            depth.pop();
            
            if(pool[sr][sc] >= 1 && pool[sr][sc] <=6 && pool[sr][sc] < size ){ // eat fish
                isEatFishes = true;
                
                if(d == temp_d)
                {
                    if(temp_r == sr)
                    {
                        if(temp_c > sc){
                            temp_r = sr;
                            temp_c = sc;
                            temp_d = d;
                        }
                    }
                    else if(temp_r > sr){
                        temp_r = sr;
                        temp_c = sc;
                        temp_d = d;
                    }
                }
                else if(d < temp_d){
                    temp_r = sr;
                    temp_c = sc;
                    temp_d = d;
                }
                
            }
            
            for(int i = 0; i < 4 ; i++){ //push 4 direction
                if (sr+dir[i][0] >= 0 && sr+dir[i][0] < N && sc+dir[i][1] >= 0 && sc+dir[i][1] < N && pool[sr+dir[i][0]][sc+dir[i][1]] <= size && visited[sr+dir[i][0]][sc+dir[i][1]] != 1) {
                    q.push(pair<int,int>(sr+dir[i][0],sc+dir[i][1]));
                    depth.push(d+1);
                    visited[sr+dir[i][0]][sc+dir[i][1]] = 1;
                }
                
            }
            
        }
        
        if(isEatFishes){
            
            t+= temp_d;
            pool[originr][originc] = 0;
            originr = temp_r;
            originc = temp_c;
            pool[temp_r][temp_c] = 9;
            if((--sco) <= 0){ //growing up
                size++;
                sco = size;
            }

        }
    }while(isEatFishes);
    
    printf("%d",t);
    
    return 0;
}
