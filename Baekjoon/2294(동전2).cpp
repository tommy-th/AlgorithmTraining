//
//  2294(동전2).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 11. 15..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

int dp[10005], check[10005];
int N, K;

int main(){
    
    memset(dp, -1, sizeof(dp));
    
    int coin;
    
    cin>>N>>K;
    
    for(int i=1; i<=N; i++){
        cin>>coin;
        
        if(coin>10000 || coin<1) continue;
        if(check[coin]) continue;
        
        dp[coin] = check[coin] = 1;
        
        for(int j=1; j<=K-coin; j++){
            if(dp[j]>0){
                if(dp[j] + 1 < dp[j+coin] || dp[j+coin] == -1)
                    dp[j+coin] = dp[j]+1;
            }
        }
    }
    
    cout<<dp[K]<<endl;
    
    return 0;
}