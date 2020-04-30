//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <deque>

using namespace std;

void clean(int arr[][50],int r,int c);
int res = 0;

int main(int argc, const char * argv[]) {
    int M,N,r,c,d,cycle;
    int arr[50][50];
    int dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    
    cycle =  0;
    
    scanf("%d %d",&N,&M);
    scanf("%d %d %d",&r,&c,&d);
    
    for(int i = 0 ; i< N ; i++)
    {
        for(int j = 0 ; j < M ; j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }
    
    
    while(1)
    {
        if(cycle >= 4)
        {
            cycle = 0;
            r += dir[(d+2)%4][0];
            c += dir[(d+2)%4][1];
            continue;
        }
        else if(arr[r][c] == 1)
        {
            break;
        }
        else if(arr[r][c] == 0)
        {
            cycle = 0;
            clean(arr,r,c);
        }
        
        if((--d) < 0) d+=4;
        
        r += dir[(d)][0];
        c += dir[(d)][1];
            
        if(arr[r][c] == 0)
        {
            cycle = 0;
            continue;
        }
        
        else
        {
            cycle ++;
            r -= dir[d][0];
            c -= dir[d][1];
                
        }
        
    }
    
    printf("%d",res);
    return 0;
}


void clean(int arr[][50],int r,int c)
{
    arr[r][c] = 2;
    res ++;
    return;
}
