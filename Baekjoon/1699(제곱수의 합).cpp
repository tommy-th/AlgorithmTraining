//
//  1699(제곱수의 합).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 10. 15..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>
#include <iostream>

using namespace std;

int dp[100005];

int main(){
    
    int N;
    scanf("%d", &N);
    
    dp[1] = 1;
    for(int i=2; i<=N; i++){
        int value = 100000;
        
        for(int j=1; j<=N; j++){
            if (j*j > i) break;
            value = min(value, dp[i-j*j]+1);
        }
        dp[i] = value;
    }
    
    printf("%d\n", dp[N]);
    
    return 0;
}