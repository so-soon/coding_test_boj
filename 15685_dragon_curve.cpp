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


using namespace std;

int N;
int map[101][101];
int max_x,max_y;
int curve[20][4];

void draw(void);
int check(void);

int main(int argc, const char * argv[]) {
    
    scanf("%d",&N);
    
    for(int i=0; i < N ; i++)
    {
        scanf("%d %d %d %d",&curve[i][0],&curve[i][1],&curve[i][2],&curve[i][3]);
    }
    
    max_x = 0;
    max_y = 0;
    
    draw();
    /*
    for(int i = 0 ; i <= max_x ; i ++)
    {
        for(int j = 0; j <= max_y ; j++) printf("%d ",map[i][j]);
        
        printf("\n");
    }*/
    
    printf("%d",check());
    return 0;
}

void draw(void){
    
    int dir[4][2] = {{0,1},{-1,0},{0,-1},{1,0}}; // 우 상 좌 하
    int x,y,d;
    deque<int> d_q;
    
    for(int i = 0; i < N ; i++)
    {// curve
        d_q.clear();
        x = curve[i][1];
        y = curve[i][0];
        
        map[x][y] = 1;
        for(int g = 0 ; g <= curve[i][3]; g++)
        {//generation
            if(g == 0){ // gen 0. move
                x += dir[curve[i][2]][0];
                y += dir[curve[i][2]][1];
                
                if(max_x < x) max_x = x;
                if(max_y < y) max_y = y;
                
                map[x][y] = 1;
                d_q.push_back(curve[i][2]);
            }
            else{ // gen N (n>=1) move
                for(int i = int(d_q.size()-1); i >= 0 ; i--)
                {
                    d = (d_q[i]+1)%4;
                    
                    x += dir[d][0];
                    y += dir[d][1];
                    
                    map[x][y] = 1;
                    
                    if(max_x < x) max_x = x;
                    if(max_y < y) max_y = y;
                    
                    d_q.push_back(d);
                }
                
            }
            
        }
    }
    
    return;
}

int check(void){
    int res = 0;
    
    for(int i = 0 ; i < max_x ; i++)
    {
        for(int j = 0 ; j < max_y ; j++)
        {
            if((map[i][j]+map[i][j+1]+map[i+1][j]+map[i+1][j+1]) == 4) res++;
        }
    }
    return res;
}
