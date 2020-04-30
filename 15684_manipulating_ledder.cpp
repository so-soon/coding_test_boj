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

int N,M,H;
int line[270][2];
int max_depth = 3;

using namespace std;

set<int> res;

int added_line[4][2];

void dfs(int depth);
int test(int depth);

int main(int argc, const char * argv[]) {
    
    scanf("%d %d %d",&N,&M,&H);
    
    for(int i = 0; i < M ; i++)
    {
        scanf("%d %d",&line[i][0],&line[i][1]);
        
    }
    added_line[0][0] = 0;
    added_line[0][1] = -1;
    dfs(0);
    if(res.size() == 0) printf("%d",-1);
    else printf("%d",*res.begin());
    return 0;
}

void dfs(int depth){
    if(depth > max_depth ) return;
    if(test(depth)){
        res.insert(depth);
        max_depth = depth;
        return;
    }
    else{
        for(int a = added_line[depth][0]; a <= H-1 ; a++)
        {
            for(int b = 0; b < N-1 ; b++)
            {
                if((a == added_line[depth][0]) && (b <= added_line[depth][1])) continue;
                else{
                    
                    added_line[depth+1][0] = a;
                    added_line[depth+1][1] = b;
                    dfs(depth+1);
                }
                
            }
        }
    }
    
    return;
}

inline int test(int depth){
    int temp_map[30][10]={0,};
    int x,y;
    int co = 1;
    
    for(int i = 0; i < M ; i++)
    {
        temp_map[line[i][0]-1][line[i][1]-1] = co;
        temp_map[line[i][0]-1][line[i][1]] = co++;
    }
    
    for(int n = 1; n <= depth; n++)
    {
        if(temp_map[added_line[n][0]][added_line[n][1]] != 0) return 0;
        else temp_map[added_line[n][0]][added_line[n][1]] = co;
        
        if(temp_map[added_line[n][0]][added_line[n][1]+1] != 0) return 0;
        else temp_map[added_line[n][0]][added_line[n][1]+1] = co++;
    }
    
    for(int i = 0 ; i < N ; i++)
    {
        x = 0;
        y = i;
        while((x >= 0 && x < H) && (y>=0 && y < N)){          // movement
            
            if(temp_map[x][y] != 0)
            {
                if(y == 0) {y+=1; x+=1;}
                else if(temp_map[x][y-1] != 0 && temp_map[x][y] == temp_map[x][y-1]){
                    y -= 1;
                    x += 1;
                }
                else {y += 1; x += 1;}
            }
            else {
                x += 1;
            }
        }
        if(y != i) return 0;
    }
    return 1;
}
