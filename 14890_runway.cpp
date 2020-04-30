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

int N,L;
int arr[100][100];

using namespace std;

int check_road(int x, int y, int d);
int main(int argc, const char * argv[]) {
    int res;
    scanf("%d %d",&N,&L);
    
    res = 2*N;
    
    for (int i = 0 ; i < N ; i++)
    {
        for ( int j = 0 ; j < N ; j++) scanf("%d",&arr[i][j]);
    }
    
    for(int d = 0 ; d <= 1 ; d++) // direction 0 = down 1 = right
    {
        for(int i = 0; i < N ; i ++)
        {
            res -= check_road(0+(d*i),(1-d)*i,d);
        }
    }
    printf("%d",res);
    return 0;
}


int check_road(int x, int y, int d)
{
    int dir[2] = {1-d,0+d};
    int nx,ny,cb;
    nx = x;
    ny = y;
    cb = 1;
    
    for(int i = 0 ; i < N-1 ; i++)
    {
        nx = x + dir[0];
        ny = y + dir[1];
        
        if(((nx >= N) || (ny >= N)) || ((x >= N) || (y >= N))) return 0;
        
        if (arr[x][y] != arr[nx][ny])
        {
            if((arr[x][y] - arr[nx][ny]) == -1) // x,y < nx,ny
            {
                if(cb < L) return 1;
                else cb = 1;
            }
            else if((arr[x][y] - arr[nx][ny]) == 1) // x, y > nx,ny
            {
                x=nx;
                y=ny;
                for(int j = 0; j < L-1 ; j++)
                {
                    nx += dir[0];
                    ny += dir[1];
                    if(((nx >= N) || (ny >= N)) || (arr[x][y] != arr[nx][ny])) return 1;
                }
                cb=1;
                
                if(arr[nx][ny] != arr[nx+dir[0]][ny+dir[1]])
                {
                    if(arr[nx][ny] < arr[nx+dir[0]][ny+dir[1]]) return 1;
                    else if(arr[nx][ny] > arr[nx+dir[0]][ny+dir[1]]) continue;
                }
                
                if((nx+dir[0] < N && ny+dir[1] < N) && (arr[nx][ny] < arr[nx+dir[0]][ny+dir[1]])) return 1;
                else
                {
                    x=nx+dir[0];
                    y=ny+dir[1];
                    
                    continue;
                }
            }
            else return 1;
        }
        else cb++;
        x=nx;
        y=ny;
    }
    return 0;
}
