//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string.h>
#include <algorithm>
#include <stdio.h>

using namespace std;

bool compare(pair<int,int> a , pair<int,int> b);
int main(int argc, const char * argv[]) {
    
    int r,c,k,t,tr,tc;
    int board[100][100];
    
    vector<pair<int,int> > v;
    map<int,int> m;
    
    memset(board,0,sizeof(board));
    tr=3;
    tc=3;
    t = 0;
    
    scanf("%d %d %d",&r,&c,&k);
    
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3; j++) scanf("%d",&board[i][j]);
    }
    
    while(board[r-1][c-1] != k){
        if(tr >= 100 || tc>= 100 || t>=100){
            t = -1;
            break;
        }
        m.clear();
        v.clear();
        if (tr >= tc) { // r operation
            for(int i = 0 ; i < tr ; i++){ // count
                m.clear();
                v.clear();
                for(int j = 0 ;  j < tc; j++){
                    if(board[i][j] != 0) m[board[i][j]]+=1;
                }
                
                for (map<int,int>::iterator iter = m.begin(); iter != m.end(); ++iter) {
                    v.push_back(make_pair((*iter).first,(*iter).second));
                }
                
                sort(v.begin(),v.end(),compare);
                
                if ((v.size()*2) > tc) tc = int(v.size()*2);
                
                memset(board[i], 0, sizeof(board[i]));
                
                for(int j = 0 ;  j < tc; j+=2){
                    if((j/2) >= v.size()) break;
                    board[i][j] = v[j/2].first;
                    board[i][j+1] = v[j/2].second;
                    
                }
            
            }
            
            
        }
        else{ // c operation
            for(int j = 0 ; j < tc ; j++){ // count
                m.clear();
                v.clear();
                for(int i = 0 ;  i < tr; i++){
                    if(board[i][j] != 0) m[board[i][j]]+=1;
                }
                
                for (map<int,int>::iterator iter = m.begin(); iter != m.end(); ++iter) {
                    v.push_back(make_pair((*iter).first,(*iter).second));
                }
                
                sort(v.begin(),v.end(),compare);
                
                if ((v.size()*2) > tr) tr = int(v.size()*2);
                
                for(int i = 0 ;  i < tr; i++){
                    board[i][j] = 0;
                }
                
                for(int i = 0 ;  i < tr; i+=2){
                    if((i/2) >= v.size()) break;
                    board[i][j] = v[i/2].first;
                    board[i+1][j] = v[i/2].second;
                }
            
            }
        }
        t++;
    }
    

    printf("%d",t);
    return 0;
}

bool compare(pair<int,int> a , pair<int,int> b){
    if (a.second == b.second) {
        return a.first < b.first;
    }
    else{
        return a.second < b.second;
    }
    
    return true;
}
