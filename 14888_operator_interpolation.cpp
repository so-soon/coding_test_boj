//
//  main.cpp
//  cplusplus
//
//  Created by soonhyuk on 2020/01/22.
//  Copyright © 2020 soonhyuk. All rights reserved.
//

#include <iostream>
#include <deque>

#define MAX(a,b) ((a)>(b) ? (a) : (b))
#define MIN(a,b) ((a)<(b) ? (a) : (b))


using namespace std;
int N,mini,maxi;
int arr[11];
deque<int> oper;
int op[4] = {0,};

void dfs(int depth);
void compute(deque<int> complete_deq);
int get_operator(int op,int a,int b);

int main(int argc, const char * argv[]) {
    

    mini = 1000000000;
    maxi = -1000000000;
    scanf("%d",&N);
    deque<int> a;
    
    
    for(int i = 0 ; i < N ; i++) scanf("%d",&arr[i]);
    
    for(int i = 0 ; i < 4 ; i++) scanf("%d",&op[i]);
    

    dfs(0);
        
    printf("%d\n%d",maxi,mini);
    return 0;
}

void dfs(int depth)
{
    if(depth >= N-1) compute(oper);
    else
    {
        for(int i = 0 ; i < 4 ; i++)
        {
            if(op[i])
            {
                oper.push_back(i);
                op[i]--;
                dfs(depth+1);
                op[i]++;
                oper.pop_back();
            }
        }
    }
}

void compute(deque<int> complete_deq)
{
    int temp = arr[0];
    
    for(int i = 1 ; i < N ; i++)
    {
        temp = get_operator(complete_deq[i-1], temp, arr[i]);
    }
    maxi = MAX(maxi,temp);
    mini = MIN(mini,temp);
    return;
}

int get_operator(int op,int a,int b)
{
    if(op == 0) return a+b;
    else if(op == 1) return a-b;
    else if(op == 2) return a*b;
    else return a/b;
}
