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
#include <set>
#include <queue>
#include <map>
#include <vector>

using namespace std;

int N;

int popularity[11];
map<int,vector<int> > ametrix;

void dfs(int depth,int k,int max);
void check(int max);

set<int> combi;
set<int> res;

int main(int argc, const char * argv[]) {
    int temp,amn;
    scanf("%d",&N);
    
    for(int i = 1 ; i <=N ; i++){
        scanf("%d",&temp);
        popularity[i] = temp;
    }
    
    for(int i = 1 ; i <=N ; i++){
        scanf("%d",&amn);
        for(int m = 1; m<=amn;m++){
            scanf("%d",&temp);
            ametrix[i].push_back(temp);
        }
    }
  
    for(int i = 1; (2*i)<=N; i++){
        dfs(0,0,i);
        
    }
    
    if(int(res.size()) == 0) printf("%d",-1);
    else printf("%d",*(res.begin()));
    
    return 0;
}

void dfs(int depth,int k,int max){
    if (depth == max) {
        check(max);
    }
    else{
        for (int i = k+1; i <= N; i++) {
            combi.insert(i);
            dfs(depth+1, i, max);
            combi.erase(i);
        }
        
    }
}

void check(int max){
    set<int> uncombi;
    int tot1 = 0,tot2 = 0,temp,co1=0,co2=0;
    queue<int> q;
    map<int,bool> visit;
    
    for(int i = 1 ; i <=N ; i++){
        if (combi.find(i) == combi.end()) {
            uncombi.insert(i);
        }
    }
    
    q.push(*(combi.begin()));
    visit[*(combi.begin())] = true;
    while (!(q.empty())) {
        temp = q.front();
        tot1 += popularity[temp];
        q.pop();
        co1++;
        
        for(vector<int>::iterator iter = ametrix[temp].begin(); iter != ametrix[temp].end(); ++iter){
            if ((visit.find((*iter)) == visit.end()) && (combi.find((*iter)) != combi.end()) ) {
                q.push((*iter));
                visit[(*iter)] = true;
            }
            
        }
    }
    visit.clear();
    q.push(*(uncombi.begin()));
    visit[*(uncombi.begin())] = true;
    while (!(q.empty())) {
        temp = q.front();
        tot2 += popularity[temp];
        q.pop();
        co2++;
        
        for(vector<int>::iterator iter = ametrix[temp].begin(); iter != ametrix[temp].end(); ++iter){
            if ((visit.find((*iter)) == visit.end()) && (uncombi.find((*iter)) != uncombi.end()) ) {
                q.push((*iter));
                visit[(*iter)] = true;
            }
            
        }
    }
    
    if ((co1 == max) && (co2 == N-max)) {
        res.insert(abs(tot1-tot2));
    }
    
    
}
