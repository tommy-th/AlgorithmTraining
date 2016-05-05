//
//  1613(역사).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 5. 5..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

#define MAXV 405

int N, M, S;

int sn;
int order[MAXV][MAXV], check[MAXV];

void set_table(int n){
    if(check[n]) return;
    check[n] = 1;
    
    for(int i=1; i<=N; i++){
        if(order[n][i] == -1){
            order[sn][i] = -1;
            order[i][sn] = 1;
            set_table(i);
        }
    }
}

int main(){
    
    int a, b;
    
    scanf("%d %d", &N, &M);
    
    for(int k=1; k<=M; k++){
        scanf("%d %d", &a, &b);
        
        order[a][b] = -1;
        order[b][a] = 1;
    }
    
    for(int i=1; i<=N; i++){
        sn = i;
        memset(check, 0, sizeof(check));
        set_table(i);
    }
    
    scanf("%d", &S);
    for(int i=1; i<=S; i++){
        scanf("%d %d", &a, &b);
        printf("%d\n", order[a][b]);
    }
    
    return 0;
}
