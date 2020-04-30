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
#include <utility>
#include <stdio.h>
using namespace std;

map<int, pair<int,int> > h_pos; // r , c
map<int,int> h_dir; // h_num =  dir;
pair< int,vector<int> >  board[20][20]; // board[i][j].first = color , board[i][j].second = vector of n_horse;

int dir[5][2] = {{1000,1000}, {0,1} , {0,-1} , {-1,0} , {1,0} };

void move(int r,int c,int h_num,bool isReversed);
int main(int argc, const char * argv[]) {
    

    int r,c,N,K,temp,turn = 0;
    
    bool wasBlue = false, isOverlapped = false;
    
    scanf("%d %d",&N,&K);
    
    for(int i = 1 ; i <= N ; i++){
        for(int j = 1 ; j <= N ; j++){
            scanf("%d",&temp);
            board[i][j] = pair<int, vector<int> >(temp,vector<int>());
            
        }
    }
    
    for(int i = 1 ; i <= K; i++){
        scanf("%d %d %d",&r,&c,&temp); // r, c ,h_dir
        board[r][c].second.push_back(i);
        h_pos[i] = pair<int,int>(r,c);
        h_dir[i] = temp;
    }
    
    while (turn <= 1000 && !isOverlapped) { // turn loop
        
        turn++;
        
        for(int h_num = 1 ; h_num <= K ; h_num++){
            do{
                r = h_pos[h_num].first + dir[h_dir[h_num]][0]; //next cell
                c = h_pos[h_num].second + dir[h_dir[h_num]][1];
                if(r >= 1 && r <= N && c >= 1 && c <= N){ // correct index
                    if(board[r][c].first == 0){ // white
                        move(r,c,h_num,false);
                        wasBlue = false;
                    }else if(board[r][c].first == 1){ // red
                        move(r,c,h_num,true);
                        wasBlue = false;
                    }else if(board[r][c].first == 2 && !wasBlue){ // blue
                        wasBlue = true;
                        if(h_dir[h_num]%2 == 0) h_dir[h_num] -= 1;
                        else h_dir[h_num] += 1;
                    } else if(wasBlue) wasBlue = false;
                    
                }else{ //out of index
                    if(wasBlue) wasBlue = false;
                    else {
                        wasBlue = true;
                        if(h_dir[h_num]%2 == 0) h_dir[h_num] -= 1;
                        else h_dir[h_num] += 1;
                    }
                }
                
            }while(wasBlue);

            //printf("\n move : %d \n ",h_num);
            if(board[r][c].second.size() >= 4) {
                isOverlapped = true;
                break;
            }
            
            /*printf("\n turn : %d \n",turn);
            
            for(int i = 1 ; i <= N ; i++){
                for(int j = 1 ; j<=N ;j++){
                    printf("| ");
                    for(int a = 0 ; a < 4 ; a++){
                        if(board[i][j].second.empty()) printf("%d ",0);
                        else {
                            if(a >= board[i][j].second.size()) printf("%d ",0);
                            else printf("%d ",board[i][j].second[a]);
                            
                        }
                    }
                    printf(" |");
                }
                printf("\n");
            }*/
            
        }
        
        
    }
    
    if(turn > 1000) turn = -1;
    
    printf("%d",turn);
    return 0;
}

void move(int r,int c,int h_num,bool isReversed){
    int index = 0;
    int orir,oric,size;
    orir = r - dir[h_dir[h_num]][0];
    oric = c - dir[h_dir[h_num]][1];
    bool isFind = false;
    for(int i = 0 ; i < board[orir][oric].second.size(); i++){ //find index
        if(board[orir][oric].second[i] == h_num){
            index = i;
            isFind = true;
            break;
        }
    }
    
    if(!isFind) printf("-----------------------------------------------------------------------------------");
    if(isReversed){ //red
        for(int idx = int(board[orir][oric].second.size())-1 ; idx >= index ; idx--){
            board[r][c].second.push_back(board[orir][oric].second[idx]);
            
            h_pos[board[orir][oric].second[idx]].first = r;
            h_pos[board[orir][oric].second[idx]].second = c;
            
        }
    }else{ // white
        for(int idx = index ; idx < board[orir][oric].second.size() ; idx++){
            board[r][c].second.push_back(board[orir][oric].second[idx]);
            
            h_pos[board[orir][oric].second[idx]].first = r;
            h_pos[board[orir][oric].second[idx]].second = c;
        }
    }
    size = int(board[orir][oric].second.size());
    for(int idx = index ; idx < size ; idx++){
        board[orir][oric].second.pop_back();
    }
}
