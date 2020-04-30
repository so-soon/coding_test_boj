//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <deque>
#include <set>

#define abs(a) ((a)<0 ? (-a) : (a))
#define MIN(a,b) ((a)<(b) ? (a) : (b))

int N,M;
int map[8][8];

using namespace std;

int cctv[8][3];
int cctv_size = 0;
set<int> moveset;
int cctv_dir[8] = {-1,};
int tv_combine[5] = {4,2,4,4,1};

void dfs(int n);
void safe_update(void);
int camera(int temp_map[][8],int n, int d);

int main(int argc, const char * argv[]) {
    
    int safe_n = 0;
    scanf("%d %d",&N,&M);
    
    for(int i = 0; i < N ; i++)
    {
        for(int j = 0; j < M; j++)
        {
            scanf("%d",&map[i][j]);
            
            if(map[i][j] == 0) safe_n++;
            else if(map[i][j] == 6) continue;
            else {
                cctv[cctv_size][0] = i;
                cctv[cctv_size][1] = j;
                cctv[cctv_size][2] = map[i][j];
                cctv_size ++;
            }
        }
    }
    
    dfs(0);
    
    safe_n -= *moveset.rbegin();
    
    printf("%d",safe_n);
    
    return 0;
}


void dfs(int n) {
    if(n == cctv_size) safe_update();
    else{
        for(int i = 0; i < tv_combine[cctv[n][2]-1] ; i++)
        {
            cctv_dir[n] = i;
            dfs(n+1);
        }
    }
    
    return;
}

void safe_update(void)
{
    int temp_map[8][8];
    int temp_move = 0;
    for(int i = 0 ; i < N ; i ++)
    {
        for(int j = 0; j < M ; j++) temp_map[i][j] = map[i][j];
    }
    
    for(int i = 0; i < cctv_size; i++)
    {
        if(cctv[i][2] == 1) temp_move += camera(temp_map,i,cctv_dir[i]);
        else if(cctv[i][2] == 2){
            temp_move += camera(temp_map,i,cctv_dir[i]);
            temp_move += camera(temp_map,i,(cctv_dir[i]+2)%4);
        }
        else if(cctv[i][2] == 3){
            temp_move += camera(temp_map,i,cctv_dir[i]);
            temp_move += camera(temp_map,i,(cctv_dir[i]+1)%4);
        }
        else if(cctv[i][2] == 4){
            temp_move += camera(temp_map,i,cctv_dir[i]);
            temp_move += camera(temp_map,i,(cctv_dir[i]+1)%4);
            temp_move += camera(temp_map,i,(cctv_dir[i]+2)%4);
        }
        else if(cctv[i][2] == 5){
            temp_move += camera(temp_map,i,cctv_dir[i]);
            temp_move += camera(temp_map,i,(cctv_dir[i]+1)%4);
            temp_move += camera(temp_map,i,(cctv_dir[i]+2)%4);
            temp_move += camera(temp_map,i,(cctv_dir[i]+3)%4);
        }
        
    }
    
    moveset.insert(temp_move);
    return;
}

int camera(int temp_map[][8],int n, int d)
{
    int move = 0;
    int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    
    int x = cctv[n][0];
    int y = cctv[n][1];
    
    while(x < N && y < M && x >= 0 && y >= 0){
        if(temp_map[x][y] == 6) return move;
        else if(temp_map[x][y] == 0)
        {
            move++;
            temp_map[x][y] = 7;
        }
        x += dir[d][0];
        y += dir[d][1];
        
    }
    return move;
    
}
