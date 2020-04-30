//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <deque>
#include <cstdio>

#define abs(a) ((a)<0 ? (-a) : (a))
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define np(a,d) (((a)<(d)) ? (((a)-(d)) % 8 + 8) : ((a)-(d)) % 8)
#define nabs(a,d) ((a)<0 ? (a)+(d) : (a))

char gear[6][8];
int head[6] = {0,};
int tail[6] = {0,};
int rot_flag[4] = {0,};
using namespace std;

void rotation(int n, int d);

int main(int argc, const char * argv[]) {
    int k,res;
    int rotate[100][2];
    int score[4] = {1,2,4,8};
    res = 0;
    

    for(int i = 0; i < 4 ; i ++)
    {
        scanf("%s",gear[i+1]);
        
        head[i+1] = 6;
        tail[i+1] = 2;
    }
    gear[0][0] = -100;
    gear[5][0] = -100;
    
    scanf("%d",&k);
    
    for(int i = 0 ; i < k ; i++)
    {
        scanf("%d %d",&rotate[i][0],&rotate[i][1]);
    }
    
    for(int i  = 0 ; i < k ; i++)
    {
        rotation(rotate[i][0],rotate[i][1]);
        for(int j = 0 ; j < 4 ; j++)
            rot_flag[j] = 0;
    }
    
    for(int i = 1; i <= 4 ; i++)
    {
        if((int(gear[i][nabs((tail[i]-2)%8,8)])-48) == 1) res += score[i-1];
    }
    printf("%d",res);
    return 0;
}


void rotation(int n, int d)
{
    if (n < 1 || n > 4 || (rot_flag[n-1]==1)) return;
    else
    {
        rot_flag[n-1] = 1;
        if((int(gear[n][head[n]])-48 + int(gear[n-1][tail[n-1]])-48) == 1 ) rotation(n-1, d*(-1));
        if((int(gear[n][tail[n]])-48 + int(gear[n+1][head[n+1]])-48) == 1 ) rotation(n+1, d*(-1));
        head[n] = np(head[n],d);
        tail[n] = np(tail[n],d);
        
        
    }
    
    return;
}
