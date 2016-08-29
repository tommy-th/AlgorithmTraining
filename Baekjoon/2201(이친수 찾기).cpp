//
//  2201(이친수 찾기).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 8. 30..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>

#define LL long long

LL K;
LL dp[100005];

int main(){
    
    int prev, cur;
    
    scanf("%lld", &K);
    
    dp[0] = dp[1] = 1;
    for (int i=1; i<=90; i++){
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    prev = cur = 0;
    
    while(K){
        for(int i=0; i<=90; i++){
            if(K<dp[i]){
                cur = i-1;
                break;
            }
        }
        
        if (prev > cur){
            printf("1");
            
            for(int j=0; j<prev-cur-1; j++)
                printf("0");
        }
        
        K -= dp[cur];
        prev = cur;
    }
    
    printf("1");
    
    for(int j=0; j<prev-1; j++)
        printf("0");
    
    printf("\n");
    
    return 0;
}
