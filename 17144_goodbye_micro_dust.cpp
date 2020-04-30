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



int main(int argc, const char * argv[]) {
    int filter_1=0,filter_2=0,R,C,T,co,size;
    int A[50][50];
    int temp[50][50];
    int res = 0;
    scanf("%d %d %d",&R,&C,&T);
    
    for(int i = 0; i < R ; i++){
        for(int j = 0 ; j < C ; j++){
            scanf("%d",&A[i][j]);
            if(A[i][j] == -1 && filter_1 == 0){
                filter_1 = i;
                filter_2 = i+1;
            }
            else if(A[i][j] != 0 && A[i][j] != -1){
                res += A[i][j];
            }
        }
    }
    
    for(int time = 0 ; time < T ; time++) //main loop
    {
        
        //printf("\n after spread-------------------------------------------\n");
        memset(temp,0,sizeof(temp));
        for(int i = 0 ; i < R ; i++){ //spread dust
            for(int j = 0 ; j < C; j++){
                co = 0;
                if(A[i][j] > 0){
                    if((i-1) >= 0){ //up
                        if(A[i-1][j] != -1){
                            temp[i-1][j] += A[i][j]/5;
                            co++;
                        }
                    }
                    if((i+1) < R){ //down
                        if(A[i+1][j] != -1){
                            temp[i+1][j] += A[i][j]/5;
                            co++;
                        }
                    }
                    if((j-1) >= 0){ //left
                        if(A[i][j-1] != -1){
                            temp[i][j-1] += A[i][j]/5;
                            co++;
                        }
                    }
                    if((j+1) < C){ //right
                        if(A[i][j+1] != -1){
                            temp[i][j+1] += A[i][j]/5;
                            co++;
                        }
                    }
                    temp[i][j] += A[i][j] - (A[i][j]/5)*co;
                }
            }
        }
        /*for(int i = 0 ; i < R ; i++){
            for(int j = 0 ; j < C; j++) printf("%d ",temp[i][j]);
            printf("\n");
        }*/
        //printf("\n-------------------------------------------\n");
        
        //printf("\n after wind-------------------------------------------\n");
        //cleaning air
        for(int i = 0; i < R ; i++){
            for(int j = 0 ; j < C ; j++){
                if(i == 0 && j != C-1){ //first row
                    A[i][j] = temp[i][j+1];
                }
                else if(i == R-1 && j!= C-1){ // last row
                    A[i][j] = temp[i][j+1];
                }
                else if((i == filter_1 || i == filter_2) && j == 1 ){
                    A[i][j] = 0;
                }
                else if(i == R-1 && j == C-1){ //last element in last row
                    A[i][j] = temp[i-1][j];
                }
                else if(i == 0 && j == C-1){ // last element in first row
                    A[i][j] = temp[i+1][j];
                }
                else if(j == 0 && i < filter_1){ // upside filter in first column
                    A[i][j] = temp[i-1][j];
                }
                else if(j == 0 && i == filter_1){ // dust into filter (upper)
                    res -= temp[i-1][j];
                }
                else if(j == 0 && i == filter_2){ //dust into filter ( lower)
                    res -= temp[i+1][j];
                }
                else if(j == 0 && i > filter_2){ //downside filter in first colmn
                    A[i][j] = temp[i+1][j];
                }
                else if((i == filter_1 || i == filter_2) && j > 1){ // filter1,2 row
                    A[i][j] = temp[i][j-1];
                }
                else if(i < filter_1 && j == C-1){ //last column upside filter1
                    A[i][j] = temp[i+1][j];
                }
                else if(i > filter_2 && j == C-1){ //last column downside filter2
                    A[i][j] = temp[i-1][j];
                }
                else A[i][j] = temp[i][j];
            }
        }
        /*for(int i = 0 ; i < R ; i++){
            for(int j = 0 ; j < C; j++) printf("%d ",A[i][j]);
            printf("\n");
        }
        printf("\n-------------------------------------------\n");
        
        */
    }
    
    printf("%d",res);
    return 0;
}
