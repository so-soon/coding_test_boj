//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <utility>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
using namespace std;


int N,M;
int board[10][10];
int dir[4][2] = { {0,1} , {1,0} , {0,-1} , {-1,0} };

set<int> res;

vector<pair<int,int> > pos_1;
queue<pair<int,int> > q;
map<pair<int,int>,bool> visit;
vector<vector<pair<int, int> > > island;
vector<pair<int, int> > temp;

vector<pair< pair<int,int> , int> > bridge; //(src,dst) , distance

int is_num = 0,r,c;
pair<int, int> connected_island;
vector<pair<int,int> > combi;
int root[7];

pair<int,int> straight(int sr,int sc,int d,int start_value);
void dfs(int depth,int k);

int find_f(int x);
void union_f(int x, int y);

bool comp(pair< pair<int,int> , int> x , pair< pair<int,int> , int> y);
int mst(void);
int main(int argc, const char * argv[]) {
    map<pair<int,int> , int>::iterator temp_iter;
    
    
    scanf("%d %d",&N,&M);
    
    for(int i = 0 ; i < N; i++){
        for(int j = 0 ; j <M; j++){
            scanf("%d",&board[i][j]);
            if(board[i][j] == 1)pos_1.push_back(pair<int,int>(i,j));
            visit[pair<int, int>(i,j)] = false;
        }
    }
    
    
    //counting island
    for(vector<pair<int,int> >::iterator iter = pos_1.begin(); iter != pos_1.end(); ++iter){
        if (!(visit[(*iter)])) {
            temp.clear();
            is_num++;
            q.push((*iter));
            visit[(*iter)] = true;
            while (!(q.empty())) {
                temp.push_back(q.front());
                r = q.front().first;
                c = q.front().second;
                board[r][c] = is_num;
                q.pop();
                
                for(int i = 0 ; i < 4 ; i++){
                    if ((r+dir[i][0] >= 0 && r+dir[i][0] < N && c+dir[i][1] >=0 && c+dir[i][1] < M) && (visit[pair<int, int>(r+dir[i][0],c+dir[i][1])] == false) && board[r+dir[i][0]][c+dir[i][1]] == 1 ) {
                        q.push(pair<int, int>(r+dir[i][0],c+dir[i][1]));
                        visit[pair<int, int>(r+dir[i][0],c+dir[i][1])] = true;
                    }
                    
                }
            }
            island.push_back(temp);

            
        }
        
    }
    
    
    
    //each island
    
    for(int i = 1 ; i <= island.size() ; i++){
        for(vector<pair<int, int> >::iterator iter = island[i-1].begin(); iter != island[i-1].end() ; ++iter){
            for(int d = 0 ; d < 4 ; d++){ // right down left up
                connected_island = straight((*iter).first, (*iter).second, d,board[(*iter).first][(*iter).second]);
                if(connected_island.first != -1){
                    if (i <= connected_island.first) {
                        //root[connected_island.first] = i;
                        bridge.push_back(pair< pair<int,int> , int>(pair<int,int>(i,connected_island.first),connected_island.second));
                    }
                }
            }
            
        }
        
    }/*
    printf("\n");
    printf("\n");
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < M ; j++) printf("%d ",board[i][j]);
        printf("\n");
    }
    printf("\n");
    
    */
    printf("%d",mst());
    
    return 0;
}


pair<int,int> straight(int sr,int sc,int d,int start_value){
    int dis = 0;
    sr+=dir[d][0];
    sc+=dir[d][1];
    
    while (sr>=0 && sr<N && sc>=0 && sc<M) {
        
        if(board[sr][sc] != 0 ){
            if (board[sr][sc] == start_value) {
                return pair<int,int>(-1,-1);
            }
            else if(dis < 2){
                return pair<int,int>(-1,-1);
            }else {
                return pair<int,int>(board[sr][sc],dis);
            }
        }
        sr+=dir[d][0];
        sc+=dir[d][1];
        dis++;
    }
    
    return pair<int,int>(-1,-1);
}

int mst(void){ //vector<pair< pair<int,int> , int> > bridge
    int temp_tot = 0 ,co = 0;
    sort(bridge.begin(),bridge.end(),comp);
    for(int i = 1 ; i < 7 ; i++) root[i] = i;
    
    for(int i = 0 ; i < bridge.size(); i++){
        if (find_f(bridge[i].first.first) == find_f(bridge[i].first.second)) { //cycle
            continue;
        }else{
            union_f(bridge[i].first.first, bridge[i].first.second);
            temp_tot += bridge[i].second;
            co++;
        }
        
    }
    
    if (co == int(island.size())-1) {
        return temp_tot;
    }
    else return -1;
}
/*
void dfs(int depth,int k){
    int temp_tot = 0,left_co = 0;
    
    map<pair<int,int> , int> ::iterator iter=bridge.begin();
    if (depth >= island.size()-1) {
        
        
        sort(combi.begin(), combi.end(), comp);
        
        for(int i = 0 ; i < combi.size(); i++){
            if (find_f(combi[i].first) == find_f(combi[i].second)) {
                
            }
            
            
        }
            
            
        }
        if(left_co == 0) {
            if(temp_tot == 16){
                printf("\n");
                printf("\n");
                for(int i = 0 ; i < depth; i++) printf("%d -> %d : %d\n",combi[i].first,combi[i].second,bridge[combi[i]]);
            }
            res.insert(temp_tot);
        }
    
    
    
    
    
    for(int i = 0 ; i < k ; i++) iter++;
    
    for(int i = k; i < int(bridge.size()); i++){
        if (combi.size() <= depth) {
            combi.push_back((*iter).first);
            dfs(depth+1, i+1);
        }
        else{
            combi[depth] = (*iter).first;
            dfs(depth+1, i+1);
        }
        iter++;
    }
    
}
*/
int find_f(int x){
    if (root[x] == x) {
        return x;
    }
    else{
        return find_f(root[x]);
    }
    
}

void union_f(int x, int y){
    x = find_f(x);
    y = find_f(y);
    
    
    root[y] = x;
}
bool comp(pair< pair<int,int> , int> x , pair< pair<int,int> , int> y){ //vector<pair< pair<int,int> , int> > bridge;
    return x.second < y.second;
    
}

