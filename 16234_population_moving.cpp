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

deque<pair<int,int>> unions;

int N,L,R;
int a[52][52];

int main(int argc, const char * argv[]) {
    int res,curx,cury;
    int visited[52][52];
    int temp[52][52];
    bool changed;
    int co,sum;
    
    changed = true;
    
    
    deque<pair<int, int>>::iterator iter;
    deque<pair<int, int>> q;
    
    // a init
    
    res = 0;
    memset(a,0,sizeof(a));
    scanf("%d %d %d",&N,&L,&R);
    
    for(int i = 1 ; i <= N ; i++)
    {
        for(int j = 1 ; j <= N ; j++) scanf("%d",&a[i][j]);
    }
    
    
    while(changed){
        //visited,temp init
        
        memset(visited,0,sizeof(visited));
        memset(temp, -1, sizeof(temp));
    
        changed =false;
        
        for(int r = 1 ; r <= N ; r++)
        {
            for(int c = 1 ; c <= N ; c++)
            {
                if(visited[r][c] != 1) // bfs each nation
                {
                    co=0;
                    sum=0;
                    q.push_back(pair<int, int>(r,c));
                    
                    while(!q.empty())
                    {
                        curx=q.front().first;
                        cury=q.front().second;
                        q.pop_front();
                        
                        if(visited[curx][cury] == 1) continue;
                        visited[curx][cury] = 1;
                        
                        if(visited[curx-1][cury] == 0 && curx!=1 && abs(a[curx][cury]-a[curx-1][cury]) >= L && abs(a[curx][cury]-a[curx-1][cury]) <= R) q.push_back(pair<int, int>(curx-1,cury));
                        if(visited[curx][cury-1] == 0 && cury!=1 && abs(a[curx][cury]-a[curx][cury-1]) >= L && abs(a[curx][cury]-a[curx][cury-1]) <= R) q.push_back(pair<int, int>(curx,cury-1));
                        if(visited[curx+1][cury] == 0 && curx!=N && abs(a[curx][cury]-a[curx+1][cury]) >= L && abs(a[curx][cury]-a[curx+1][cury]) <= R) q.push_back(pair<int, int>(curx+1,cury));
                        if(visited[curx][cury+1] == 0 && cury!=N && abs(a[curx][cury]-a[curx][cury+1]) >= L && abs(a[curx][cury]-a[curx][cury+1]) <= R) q.push_back(pair<int, int>(curx,cury+1));
                        
                        
                        
                        unions.push_back(pair<int,int>(curx,cury));
                        co++;
                        sum+=a[curx][cury];
                    } //end find one union
                    
                    //assign values to the union
                    
                    for(iter=unions.begin() ; iter != unions.end() ; iter++)
                    {
                        temp[iter->first][iter->second] = sum/co;
                    }
                    
                    unions.clear();
                }
                
                
            }
        }
        
        //temp assign
        for(int r = 1; r <= N ; r++)
        {
            for(int c = 1 ; c <= N ; c++)
            {
                if(temp[r][c] != a[r][c])
                {
                    a[r][c] = temp[r][c];
                    changed = true;
                }
            }
        }
        if(changed) res++;
    }
    
    printf("%d",res);
    
    return 0;
}
