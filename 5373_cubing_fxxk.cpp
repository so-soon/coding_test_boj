//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>


using namespace std;



char real_cube[3][3][3][6];





void rotat(int n,char dimension,char dir);
void rotate_mini(int d,int ddd,char* c);

int main(int argc, const char * argv[]) {
    int t;
    int n;
    char order[4000];
    scanf("%d",&t);
    
    for(int i = 0 ; i < t ; i++)
    {
        scanf("%d",&n);
        for(int a = 0 ; a < 3 ;a++)
        {
            for(int b = 0 ; b < 3 ; b++)
            {
                for(int c = 0 ; c < 3; c++)
                {
                    real_cube[a][b][c][0] = 'w';
                    real_cube[a][b][c][1] = 'b';
                    real_cube[a][b][c][2] = 'y';
                    real_cube[a][b][c][3] = 'g';
                    real_cube[a][b][c][4] = 'o';
                    real_cube[a][b][c][5] = 'r';
                    
                }
            }
        }
        for(int j = 0 ; j < n ; j++)
        {
            scanf("%s",order);
            rotat(n,order[0],order[1]);
        }
        
        for(int r = 2 ; r >= 0 ; r--)
        {
            for(int c = 0; c < 3 ; c++) printf("%c",real_cube[0][c][r][0]);
            printf("\n");
        }
    }
    return 0;
}

void rotat(int n,char dimension,char dir)
{
    char temp[3][3][6];
    int d;
    
    if(dir == '+')
    {
        d = 1;
    }
    else
    {
        d = -1;
    }
    
    if(dimension == 'F')
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                for(int n = 0; n < 6 ; n++) temp[i][j][n] = real_cube[i][j][0][n];
                rotate_mini(d, 2, temp[i][j]);
            }
        }
        
        if(d == 1)
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][j][0][n] = temp[2-j][i][n];
                   }
               }
           }
           else
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][j][0][n] = temp[j][2-i][n];
                   }
               }
           }
    }
    
    else if(dimension == 'B')
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                for(int n = 0; n < 6 ; n++) temp[i][j][n] = real_cube[i][j][2][n];
                rotate_mini((d*(-1)), 2, temp[i][j]);
            }
        }
        
        if(d == -1)
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][j][2][n] = temp[2-j][i][n];
                   }
               }
           }
           else
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][j][2][n] = temp[j][2-i][n];
                   }
               }
           }
    }
    else if(dimension == 'L')
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                for(int n = 0; n < 6 ; n++) temp[i][j][n] = real_cube[i][0][j][n];
                rotate_mini((d*(-1)), 1, temp[i][j]);
            }
        }
        
        if(d == -1)
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][0][j][n] = temp[2-j][i][n];
                   }
               }
           }
           else
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][0][j][n] = temp[j][2-i][n];
                   }
               }
           }
    }
    else if(dimension == 'R')
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                for(int n = 0; n < 6 ; n++) temp[i][j][n] = real_cube[i][2][j][n];
                rotate_mini(d, 1, temp[i][j]);
            }
        }
        
        if(d == 1)
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][2][j][n] = temp[2-j][i][n];
                   }
               }
           }
           else
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[i][2][j][n] = temp[j][2-i][n];
                   }
               }
           }
    }
    else if(dimension == 'U')
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                for(int n = 0; n < 6 ; n++) temp[i][j][n] = real_cube[0][i][j][n];
                rotate_mini(d, 0, temp[i][j]);
            }
        }
        
        if(d == 1)
           {
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[0][i][j][n] = temp[2-j][i][n];
                   }
               }
           }
           else
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[0][i][j][n] = temp[j][2-i][n];
                   }
               }
           }
    }
    else if(dimension == 'D')
    {
        for(int i = 0 ; i < 3 ; i++)
        {
            for(int j = 0 ; j < 3 ; j++)
            {
                for(int n = 0; n < 6 ; n++) temp[i][j][n] = real_cube[2][i][j][n];
                rotate_mini((d*(-1)), 0, temp[i][j]);
            }
        }
        
        if(d == -1)
           {
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[2][i][j][n] = temp[2-j][i][n];
                   }
               }
           }
           else
           {
               
               for(int i = 0 ; i < 3 ; i++)
               {
                   for(int j = 0 ; j < 3 ; j++)
                   {
                       for(int n = 0 ; n < 6; n++) real_cube[2][i][j][n] = temp[j][2-i][n];
                   }
               }
           }
    }
    return;
}


void rotate_mini(int d,int ddd,char* c)
{
    char temp;
 
    if(ddd == 0) // 위아래 잡고
    {
        if(d==1)
        {
            temp = c[5];
            c[5] = c[1];
            c[1] = c[4];
            c[4] = c[3];
            c[3] = temp;
        }
        else
        {
            
            temp = c[5];
            c[5] = c[3];
            c[3] = c[4];
            c[4] = c[1];
            c[1] = temp;
        }
    }
    else if(ddd == 1)// 왼오른 잡고
    {
        if(d==1)
        {
            temp = c[5];
            c[5] = c[2];
            c[2] = c[4];
            c[4] = c[0];
            c[0] = temp;
        }
        else
        {
            temp = c[0];
            c[0] = c[4];
            c[4] = c[2];
            c[2] = c[5];
            c[5] = temp;
        }
    }
    else // 앞뒤 잡고
    {
        if(d==1)
        {
            temp = c[0];
            c[0] = c[3];
            c[3] = c[2];
            c[2] = c[1];
            c[1] = temp;
        }
        else
        {
            temp = c[0];
            c[0] = c[1];
            c[1] = c[2];
            c[2] = c[3];
            c[3] = temp;
        }
    }
}
