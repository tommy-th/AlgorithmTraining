//
//  Lucas_theorem_test.cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 1. 8..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

#define MEMSET(arr) memset(arr, 0, sizeof(arr))
#define MOD 1000000007
#define LL long long

LL D;
int N, R, T;
int pecto[2005], exps[2005], dp[2005][2005], subset[2005][2005];

void init(){
    MEMSET(dp);
    MEMSET(subset);
}

int sum(int a, int b){
    return ((long long)a + b) % MOD;
}

int mul(int a, int b){
    return ((long long)a * b) % MOD;
}

void set_dp(){
    int offset;
    
    for (int i=1; i <= N; i++) {
        if(i < R) dp[i][1] = 1;
        subset[i][1] = subset[i-1][1]+dp[i][1];
    }
    
    for(int i=2; i<=N; i++) {
        offset = i-R > 0 ? i-R : 0;
        
        for(int j=2; j<=i; j++) {
            dp[i][j] = subset[i-1][j-1] - subset[offset][j-1];
            if(dp[i][j] < 0) dp[i][j] += MOD;
            subset[i][j] = sum(subset[i-1][j], dp[i][j]);
        }
    }
}

// return n^e (mod MOD)
int mod_pow(int n, int e){
    if (e == 0) return 1;
    if (e == 1) return n;
    if (e % 2 == 0) return mod_pow(mul(n, n), e / 2);
    else return mul(n, mod_pow(mul(n, n), e / 2));
}

void set_ferma(){
    pecto[0] = exps[0] = 1;
    
    for (int i = 1; i <= 2000; i++){
        pecto[i] = mul(pecto[i - 1] , i);
    }
    for (int i = 1; i <= 2000; i++){
        exps[i] = mod_pow(pecto[i], MOD - 2);
    }
}

int hVal;

int combi(int n, int r){
    if(r>n) return 0;
    if(r==n) return 1;
    
    hVal = mul(hVal, n-r+1);
    return mul(hVal, exps[r]);
  }

int lucas(LL n, int r){
    int ret = combi(n % MOD, r);
    
    return ret;
}

int ans(){
    int ret=0;
    
    hVal = 1;
    for(int i=1; i<=N; i++){
        if(hVal ==0) break;
        
        ret = sum(ret, mul(lucas(D, i), dp[N][i]));
    }
    
    return ret;
}

int main(){
    int result;
    
    if (freopen("sample_input.txt", "r", stdin) == NULL){
        fprintf(stderr, "Fail to load input text file\n");
        exit(0);
    }
    freopen("sample_output.txt", "w", stdout);
    
    set_ferma();
    
    cin>>T;
    for(int t=1; t<=T; t++){
        init();
        cin>>N>>D>>R;
        
        set_dp();
        result = ans();
        
        cout<<result<<endl;
    }
    
    fprintf(stderr, "Completed!\n");
    
    return 0;
}