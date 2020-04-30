//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <deque>

#define abs(a) ((a)<0 ? (-a) : (a))
#define MIN(a,b) ((a)<(b) ? (a) : (b))


using namespace std;

int N;
int s[20][20];
int player[20];
int mini=1000000000;

void dfs(int depth,int idx);
//void compute(deque<int> team);

int main(int argc, const char * argv[]) {
    
    
    scanf("%d",&N);
    for(int i = 0 ; i < N ; i ++)
    {
        for(int j = 0 ; j < N ; j ++)
        {
            scanf("%d",&s[i][j]);
        }
        player[i] = 1;
    }
    
    dfs(0,0);
    
    printf("%d",mini);
    return 0;
}


void dfs(int depth,int idx)
{
    if(depth >= (N/2))
    {
        deque<int> team,team2;
        int sum1,sum2;
        sum1 = 0;
        sum2 = 0;
        for(int i = 0 ; i < N ; i++)
        {
            if(player[i]) team2.push_back(i);
            else team.push_back(i);
        }
        
        for(int i = 0 ; i < (N/2) ; i++)
        {
            for(int j = i ; j < (N/2) ; j++)
            {
                sum1 += s[team[i]][team[j]] + s[team[j]][team[i]];
                sum2 += s[team2[i]][team2[j]] + s[team2[j]][team2[i]];
                
            }
        }
        mini = MIN(mini,abs((sum1-sum2)));
    }
    else
    {
        for(int i = idx ; i < N ; i++)
        {
            if(player[i])
            {
                player[i]--;
                dfs(depth+1,i+1);
                player[i]++;
            }
        }
    }
}

/*
void compute(deque<int> team)
{
    deque<int> team2;
    int sum1,sum2;
    sum1 = 0;
    sum2 = 0;
    for(int i = 0 ; i < N ; i++)
    {
        if(player[i]) team2.push_back(i);
    }
    
    for(int i = 0 ; i < (N/2) ; i++)
    {
        for(int j = i ; j < (N/2) ; j++)
        {
            sum1 += s[team[i]][team[j]] + s[team[j]][team[i]];
            sum2 += s[team2[i]][team2[j]] + s[team2[j]][team2[i]];
            
        }
    }
    mini = MIN(mini,abs((sum1-sum2)));
}
*/
