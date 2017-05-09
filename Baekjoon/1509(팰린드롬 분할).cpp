//
//  1509(팰린드롬 분할).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 11. 15..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

char input[2510];

int N;
int isPal[2510][2510];
int dp[2510];

void set_table(){
    
    for(int i=1; i<=N; i++)
        isPal[i][i] = 1;
    
    for(int i=1; i<=N-1; i++){
        if (input[i]==input[i+1])
            isPal[i][i+1] = 1;
    }
    
    for(int k=2; k<=N; k++){
        for(int j=1; j<=N; j++){
            if(j+k > N) break;
            
            if(isPal[j+1][j+k-1] && input[j] == input[j+k])
                isPal[j][j+k] = 1;
        }
    }
}

int get_result(){
    
    memset(dp, -1, sizeof(dp));
    
    dp[0] = 0;
    
    for(int i=1; i<=N; i++){
        for(int j=i; j<=N; j++){
            if(isPal[i][j]){
                int temp = dp[i-1] + 1;
                
                if(dp[j]==-1 || temp < dp[j])
                    dp[j] = temp;
            }
        }
    }
    
    return dp[N];
}

int main(){
    
    scanf("%s", &input[1]);
    
    N = (int)strlen(&input[1]);
    
    set_table();
    
    printf("%d\n", get_result());
    
    return 0;
}
