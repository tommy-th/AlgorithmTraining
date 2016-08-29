//
//  1328(고층빌딩).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 8. 29..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>

#define LL long long
#define MOD 1000000007

int N, L, R;


LL pecto[105];
LL combi[105][105];

LL counts[105][105];


void set_pecto(){
    pecto[0] = 1;
    
    for(int i=1; i<=100; i++){
        pecto[i] = (LL)(pecto[i-1]*i) % MOD;
    }
}

void set_combi(){
    for(int i=0; i<=100; i++)
        combi[i][0] = 1;
    
    for(int i=1; i<=100; i++){
        for(int j=1; j<=i; j++){
            combi[i][j] = (LL)(combi[i-1][j-1] + combi[i-1][j]) % MOD;
        }
    }
}

void set_counts(){
    
    counts[0][0] = counts[1][1] = 1;
    
    for(int i=2; i<=N; i++){
        
        counts[i][1] = pecto[i-1];
        
        for(int j=2; j<=i; j++){
            
            for(int k=j-1; k<i; k++){
                LL buf = (LL)(combi[i-1][k]*counts[k][j-1]) % MOD;
                buf = (LL)(buf*pecto[i-1-k]) % MOD;
                counts[i][j] = (LL)(counts[i][j] + buf) % MOD;
            }
        }
    }
}

LL result(){
    LL ret = 0;
    
    for(int left=L-1; left<N; left++){
        int right = N - 1 - left;
        if (right < R-1) break;
        
        LL buf = combi[N-1][left];
        buf = (LL)(buf*counts[left][L-1]) % MOD;
        buf = (LL)(buf*counts[right][R-1]) % MOD;
        
        ret = (LL)(ret+buf) % MOD;
    }
    
    return ret;
}


int main(){
    
    scanf("%d %d %d", &N, &L, &R);
    
    set_pecto();
    set_combi();
    set_counts();
    
    printf("%lld\n", result());
    
    return 0;
}