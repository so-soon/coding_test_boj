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

void wall_dfs(int arr[][8],int depth);
void spear_virus(int arr[][8]);
deque<int> virus;
int safe = 0;
int N,M;
int maximum = 0;

int main(int argc, const char * argv[]) {
    int arr[8][8]={0,};
    scanf("%d %d",&N,&M);
    
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            arr[i][j] = -1;
        }
        
    }
    
    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < M ; j++)
        {
            scanf("%d",&arr[i][j]);
            if(arr[i][j] == 0) safe++;
            else if(arr[i][j] == 2)
            {
                virus.push_back(i);
                virus.push_back(j);
            }
        }
        
    }

    wall_dfs(arr,0);
    printf("%d",maximum-3);
    return 0;
}

void wall_dfs(int arr[][8],int depth)
{
    if(depth > 2)
    {
        spear_virus(arr);
        
    }
    else
    {
        for(int i = 0 ; i < N ; i++)
        {
            for(int j = 0 ; j < M ; j++)
            {
                if(arr[i][j] == 0)
                {
                    arr[i][j] = 1;
                    wall_dfs(arr,depth+1);
                    arr[i][j] = 0;
                }
                else
                {
                    continue;
                }
            }
            
        }
    }
    return;
}

void spear_virus(int arr[][8])
{
    int map1[8][8];
    int t_i,t_j;
    int t_safe = safe;
    deque<int> bfs;
    
    bfs.assign(virus.begin(),virus.end());
    
    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < M ; j++)
        {
            map1[i][j] = arr[i][j];
        }
        
    }

    while(!bfs.empty())
    {
        t_i = bfs[0];
        t_j = bfs[1];
        bfs.pop_front();
        bfs.pop_front();
        
        if(map1[t_i][t_j] == 0)
        {
            t_safe --;
            map1[t_i][t_j] = 2;
        }
        
        if((t_i-1) >=0)
        {
            if(map1[t_i-1][t_j] == 0)
            {
                bfs.push_back(t_i-1);
                bfs.push_back(t_j);
            }
        }
        if((t_i+1) < N)
        {
            if(map1[t_i+1][t_j] == 0)
            {
                bfs.push_back(t_i+1);
                bfs.push_back(t_j);
            }
        }
        if((t_j-1) >=0)
        {
            if(map1[t_i][t_j-1] == 0)
            {
                bfs.push_back(t_i);
                bfs.push_back(t_j-1);
            }
        }
        if((t_j+1) < M)
        {
            if(map1[t_i][t_j+1] == 0)
            {
                bfs.push_back(t_i);
                bfs.push_back(t_j+1);
            }
        }
        
    }
 
    
    if(maximum < t_safe) maximum = t_safe;
    
}
