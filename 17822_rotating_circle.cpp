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
#include <set>
#include <utility>
#include <stdio.h>

using namespace std;


int pos_calc(int pos,int next,int d); // pos에서 d방향으로 next칸 있는값의 index


int circle[50][50];
int N,M,T;
map<int,int> front;

int main(int argc, const char * argv[]) {
    int tot = 0, temp_j,co = 0;
    float ave;
    int x,d,k;
    
    set<pair<int,int> > dele;
    scanf("%d %d %d",&N,&M,&T);
    
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++){
            scanf("%d",&circle[i][j]);
            tot+=circle[i][j];
            co++;
        }
        front[i] = 0;
    }

    for(int i = 0 ; i < T; i++){
        scanf("%d %d %d",&x,&d,&k);
        
        dele.clear();
        
        for(int cn = 0 ; cn < N ; cn++){ //check each circle
            if((cn+1) % x == 0){ //rotate
                front[cn] = pos_calc(front[cn], k, d);
            }
        }
        for(int cn = 0 ; cn < N ; cn++){
            for(int j = 0 ; j < M ; j++){
                temp_j = pos_calc(front[cn], j, 1);
                if(cn == 0){
                    if((circle[cn][temp_j] == circle[cn+1][pos_calc(front[cn+1], j, 1)]) && circle[cn][temp_j] > 0) {
                        dele.insert(pair<int,int>(cn,temp_j));
                        dele.insert(pair<int,int>(cn+1,pos_calc(front[cn+1], j, 1)));
                    }
                }else if(cn == N-1){
                    if((circle[cn][temp_j] == circle[cn-1][pos_calc(front[cn-1], j, 1)]) && circle[cn][temp_j] > 0) {
                        dele.insert(pair<int,int>(cn,temp_j));
                        dele.insert(pair<int,int>(cn-1,pos_calc(front[cn-1], j, 1)));
                    }
                }else{
                    if((circle[cn][temp_j] == circle[cn+1][pos_calc(front[cn+1], j, 1)]) && circle[cn][temp_j] > 0) {
                        dele.insert(pair<int,int>(cn,temp_j));
                        dele.insert(pair<int,int>(cn+1,pos_calc(front[cn+1], j, 1)));
                    }
                    if((circle[cn][temp_j] == circle[cn-1][pos_calc(front[cn-1], j, 1)]) && circle[cn][temp_j] > 0) {
                        dele.insert(pair<int,int>(cn,temp_j));
                        dele.insert(pair<int,int>(cn-1,pos_calc(front[cn-1], j, 1)));
                    }
                }
                
                if((circle[cn][temp_j] == circle[cn][pos_calc(temp_j, 1, 0)]) && circle[cn][temp_j] > 0) {
                    dele.insert(pair<int,int>(cn,temp_j));
                    dele.insert(pair<int,int>(cn,pos_calc(temp_j, 1, 0)));
                }
                if((circle[cn][temp_j] == circle[cn][pos_calc(temp_j, 1, 1)]) && circle[cn][temp_j] > 0) {
                    dele.insert(pair<int,int>(cn,temp_j));
                    dele.insert(pair<int,int>(cn,pos_calc(temp_j, 1, 1)));
                }
                
            }
         
        }
            
        
        
        for(set<pair<int,int> >::iterator iter = dele.begin() ; iter != dele.end() ; ++iter){
            
            tot -= circle[(*iter).first][(*iter).second];
            circle[(*iter).first][(*iter).second] = -1;
            co--;
        }
        //printf("\n tot : %d co : %d \n",tot,co);
        if(dele.size() == 0){
            ave = float(tot)/float(co);
            for(int cn = 0 ; cn < N ; cn++){
                for(int j = 0 ; j < M ; j++){
                    temp_j = pos_calc(front[cn], j, 1);
                    if(float(circle[cn][temp_j]) > ave && circle[cn][temp_j] >= 0){
                        circle[cn][temp_j] -= 1;
                        tot -=1;
                    }
                    else if(float(circle[cn][temp_j]) < ave && circle[cn][temp_j] >= 0){
                        circle[cn][temp_j] += 1;
                        tot +=1;
                    }
                    
                }
            }
        }
        
    }
    
    printf("%d",tot);
    
    return 0;
}


inline int pos_calc(int pos,int next,int d){ // pos에서 d방향으로 next칸 있는값의 index
    if(d == 1){ //reverse clock dir
        return (pos+next)%M;
    } else{
        if(pos-next < 0){
            return pos-next+M;
        }
        else{
            return pos-next;
        }
    }
    return 0;
}
