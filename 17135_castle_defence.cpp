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
#include <string.h>
#include <limits.h>
#include <list>
#include <stdlib.h>

using namespace std;

int N,M,D;
int board[100][100];

map<int,pair<int,int>> enermy;
map<int,pair<int,int>> enermy_temp;
map<int,bool> isdeath;

int main(int argc, const char * argv[]) {
    
    int archer_c[3],co=0,target,ener_co,dist,temp_res,res = INT_MIN,temp_dist;
    
    set<int> deathlist;
    
    scanf("%d %d %d",&N,&M,&D);
    
    for (int i = 0; i < N; i++) {
        for(int j = 0 ; j < M ; j++) {
            scanf("%d",&board[i][j]);
            if(board[i][j] == 1){
                enermy_temp[co].first = i;
                enermy_temp[co].second = j;
                isdeath[co++] = false;
            }
        }
    }
    for(int i = 0 ; i < M ; i++){
        for(int j = i+1 ; j < M ;j++){
            for(int k = j+1 ; k < M ; k++){
                archer_c[0] = i;
                archer_c[1] = j;
                archer_c[2] = k;
                ener_co = co;
                temp_res = 0;
                for(int en = 0 ; en < co ; en++){
                    isdeath[en] = false;
                    enermy[en].first = enermy_temp[en].first;
                    enermy[en].second = enermy_temp[en].second;
                    
                }
                
                
                while (ener_co > 0) { //1game
                    deathlist.clear();
                    
                    for(int an = 0; an < 3 ;an++){
                        dist = INT_MAX;
                        target = -1;
                        for(map<int,pair<int,int>>::iterator iter = enermy.begin(); iter != enermy.end(); ++iter){
                            temp_dist = abs(N - (*iter).second.first) + abs( archer_c[an] - (*iter).second.second );
                            if ( temp_dist < dist && temp_dist <= D && !(isdeath[(*iter).first])) {
                                dist = temp_dist;
                                target = (*iter).first;
                            } else if(temp_dist == dist && !(isdeath[(*iter).first])){
                                if((*iter).second.second < enermy[target].second){
                                    dist = temp_dist;
                                    target = (*iter).first;
                                }
                            }
                        }
                        if(dist != INT_MAX) deathlist.insert(target);
                    }
                    
                    for(set<int>::iterator iter = deathlist.begin(); iter!= deathlist.end(); ++iter){
                        ener_co--;
                        temp_res++;
                        isdeath[(*iter)] = true;
                        
                    }
                    
                    for(map<int,pair<int,int>>::iterator iter = enermy.begin(); iter != enermy.end(); ++iter){
                        if(!(isdeath[(*iter).first])){
                            (*iter).second.first+=1;
                            if((*iter).second.first >= N){
                                isdeath[(*iter).first] = true;
                                ener_co--;
                            }
                        }
                        
                    }
                }
                if(temp_res >= res) res = temp_res;
            }
        }
    }
    
    printf("%d",res);
    
    return 0;
}
