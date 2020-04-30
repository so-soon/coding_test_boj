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

//#define abs(a) ((a)<0 ? (-a) : (a))
#define MIN(a,b) ((a)<(b) ? (a) : (b))


using namespace std;

int N,M;
int map[50][50];

int house[100][2];
int h_co;

int chick[13][2];
int c_co;

set<int> res;

int combi[13];

void dfs(int depth,int n);
void check(void);

int main(int argc, const char * argv[]) {
    h_co=0;
    c_co=0;
    
    scanf("%d %d",&N,&M);
    
    for(int i = 0 ; i < N ; i++)
    {
        for(int j = 0 ; j < N ; j++)
        {
            scanf("%d",&map[i][j]);
            
            if(map[i][j] == 1)
            {
                house[h_co][0] = i;
                house[h_co++][1] = j;
                
            }
            else if(map[i][j] == 2)
            {
                chick[c_co][0] = i;
                chick[c_co++][1] = j;
                
            }
            
        }
    }
    
    dfs(0,0);
    
    printf("%d",*res.begin());
    
    return 0;
}

void dfs(int depth,int n){ // depth start with 0 , n 0
    if(depth >= M) check();
    else
    {
        for(int i = n; i < c_co ; i++)
        {
            combi[depth] = i;
            dfs(depth+1,i+1);
        }
    }
    
}

void check(void)
{
    int temp,t_sum;
    t_sum = 0;
    for(int i = 0; i < h_co; i++)
    {
        temp = 101;
        for(int j = 0 ; j < M; j++)
        {
            temp = MIN(temp,(abs(house[i][0]-chick[combi[j]][0])+abs(house[i][1]-chick[combi[j]][1])));
        
        }
        t_sum += temp;
    }
    res.insert(t_sum);
}
