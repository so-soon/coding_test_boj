#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int N,M,i,j,pi,pj,t_sum,max;
    scanf("%d %d",&N,&M);
    int arr[N][M];
    int pos[2] = {0,0};
    
    int t[19][3][2] = { {{0,1},{0,1},{0,1}},
        {{1,0},{1,0},{1,0}},
        {{0,1},{1,0},{0,-1}},
        {{1,0},{1,0},{0,1}},
        {{1,0},{0,-1},{0,-1}},
        {{0,1},{1,0},{1,0}},
        {{-1,0},{0,1},{0,1}},
        {{1,0},{0,1},{1,0}},
        {{0,1},{-1,0},{0,1}},
        {{0,1},{1,0},{-1,1}},
        {{1,0},{1,0},{-1,-1}},
        {{1,0},{1,0},{-1,1}},
        {{0,1},{-1,0},{1,1}},
        {{1,0},{1,0},{0,-1}},
        {{0,1},{0,1},{1,0}},
        {{0,-1},{1,0},{1,0}},
        {{1,0},{0,1},{0,1}},
        {{1,0},{0,-1},{1,0}},
        {{0,1},{1,0},{0,1}},
    };
    
    for(i = 0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }
    max = -1;
    
    
    
    for(pi=0;pi<N;pi++)
    {
        for(pj=0;pj<M;pj++)
        {
            
            for(i=0;i<19;i++)
            {
                
                pos[0] = pi;
                pos[1] = pj;
                
                t_sum = arr[pos[0]][pos[1]];

                
                for(j=0;j<3;j++)
                {
                    pos[0] += t[i][j][0];
                    pos[1] += t[i][j][1];
                    
                    if(pos[0] >= N || pos[0] < 0 || pos[1] >= M || pos[1] < 0)
                    {
                        break;
                    }
                    else
                    {
                        t_sum += arr[pos[0]][pos[1]];
                    }
                    
                }
                if(max < t_sum)
                {max = t_sum;}
                
                
            }
        }
        
        
    }

    printf("%d",max);
    
    return 0;
}