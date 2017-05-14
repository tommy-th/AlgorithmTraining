//
//  2.cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 6. 29..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

#define LL long long
#define MOD 1000000009


int T;
int N, K, L;

int bridge[50005];
LL dp[50505][105];

void init(){
    
    memset(dp, 0, sizeof(dp));
    memset(bridge, 0, sizeof(bridge));
}

void calc(){
    
    dp[0][0] = 1;
    
    for(int i=0; i<=N; i++){
        if(bridge[i]<0) continue;
        
        for(int j=1; j<=K; j++){
            
            int nidx = i + j;
            if(nidx > N) break;
            if(bridge[nidx]<0) continue;
            
            LL sum = dp[i][0] - dp[i][j];
            if(sum<0) sum += MOD;
            
            dp[nidx][0] += sum;
            dp[nidx][0] %= MOD;
            dp[nidx][j] += sum;
            dp[nidx][j] %= MOD;
        }
    }
}


int main(){
    
    int bomb;
    
    cin>>T;
    
    for(int t=1; t<=T; t++){
        cin>>N>>K>>L;
        
        init();
        
        for(int i=1; i<=L; i++){
            cin>>bomb;
            bridge[bomb] = -1;
        }
        calc();
        
        cout<<"Case #"<<t<<endl;
        
        cout<<dp[N][0]<<endl;
    }
    
    return 0;
}
