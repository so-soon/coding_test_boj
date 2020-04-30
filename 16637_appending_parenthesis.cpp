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
#include <stdio.h>

using namespace std;

int calc(int a,int b,char oper);
int calc_arr(map<int,bool> paren);
void dfs(int depth,map<int, bool> paren,int idx);

int N,res=INT_MIN;
char arr[19];

int main(int argc, const char * argv[]) {
    
    char trash;
    map<int,int> limit; // 괄호갯수<=limit
    map<int,bool> paren;
    scanf("%d",&N);
    
    scanf("%c",&trash);
    for(int i = 0 ; i < N; i++){
        scanf("%c",&arr[i]);
    }
    
    for(int i = 1 ; i <=19 ; i+=2){
        if(i==1) limit[i] = 1;
        else limit[i] = ((i/2)+1)/2;
    }
    
    for(int k = 0 ; k <= limit[N] ; k++){ //num of parenthesis
        dfs(k+1, paren, -2);
        
        
    }
    if(N==1) res = int(arr[0])-48;
    
    printf("%d",res);
    return 0;
}


int calc(int a,int b,char oper){
    if(oper == '+') return a+b;
    else if(oper == '-') return a-b;
    else return a*b;
    
}
int calc_arr(map<int,bool> paren){
    int tot=0,right_idx=0,right_value =0;
    
    while(right_idx < N){
        right_value = int(arr[right_idx])-48;
        if((paren.find(right_idx) == paren.end()) || paren[right_idx]==false){ //no parenthesis
            if(right_idx == 0 ) tot = calc(tot, right_value,'+');
            else {
                tot = calc(tot, right_value, arr[right_idx-1]);
            }
            right_idx += 2;
        }else{ //parenthesis
            if(right_idx == 0) tot = calc(right_value,int(arr[right_idx+2]-48),arr[right_idx+1]);
            else{
                tot = calc(tot, calc(int(arr[right_idx]-48), int(arr[right_idx+2]-48), arr[right_idx+1]), arr[right_idx-1]);
            }
            right_idx += 4;
        }
    }
    
    
    
    return tot;
}

void dfs(int depth,map<int, bool> paren,int idx){
    if(depth == 0){
        res = max(res,calc_arr(paren));
        return;
    }else{
        for(int i = idx+2 ; i < N-2 ; i+=2){
            paren[i] = true;
            dfs(depth-1,paren,i);
            paren[i] = false;
        }
    }
    
}
