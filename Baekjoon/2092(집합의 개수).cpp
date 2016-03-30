//
//  2092(집합의 개수).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 3. 30..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
using namespace std;

#define MOD 1000000

int M, N, S, E;

int nums[205];
int dp[205][4005], sums[205][4005];


int main(){
    
    int result=0;
    int input;
    
    cin>>M>>N>>S>>E;
    
    for(int i=1; i<=N; i++){
        cin>>input;
        nums[input]++;
    }
    
    for(int i=1; i<=M; i++){
        
        for(int j=1; j<=N; j++){
            
            dp[i][j] = dp[i-1][j];
            if(nums[i]>=j) dp[i][j]++;
            
            if(nums[i]>=1){
                int idx = nums[i] >= j ? 1 : j-nums[i];
                
                int prev = sums[i-1][j-1] - sums[i-1][idx-1];
                if(prev < 0) prev += MOD;
                
                dp[i][j] += prev;
                dp[i][j] %= MOD;
            }
            
            sums[i][j] = (sums[i][j-1] + dp[i][j]) % MOD;
        }
    }
    
    for(int i=S; i<=E; i++){
        result += dp[M][i];
        result %= MOD;
    }
    
    cout<<result<<endl;
    
    return 0;
}