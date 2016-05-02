//
//  1102(발전소).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 5. 1..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

int N, P;

int dp[65540], check[65540];
int min_costs[20];
int costs[20][20], states[20];
queue<pair<int, int>> paths;


void set_info(int path, int counts, int costs){
    if(dp[path] == -1 || costs < dp[path]) dp[path] = costs;
    if(min_costs[counts] == -1 || costs < min_costs[counts])
        min_costs[counts] = costs;
    if(check[path]==0){
        check[path] = 1;
        paths.push({path, counts});
    }
}

void bfs(){
    
    while(!paths.empty()){
        int path = paths.front().first, counts = paths.front().second;
        paths.pop();
        
        if(counts>P) continue;
        
        for(int i=1; i<=N; i++){
            if((path & 1<<(i-1))==0) continue;
            
            for(int j=1; j<=N; j++){
                if((path & 1<<(j-1)) != 0) continue;
            
                int npath = path | 1<<(j-1);
                
                set_info(npath, counts+1, dp[path] + costs[i][j]);
            }
        }
        
        check[path] = 0;
    }
}


int main(){
    
    int counts = 0;
    int init_path = 0;
    char input[20];

    cin>>N;
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin>>costs[i][j];
        }
    }
    
    cin>>input;
    
    for(int i=1; i<=N; i++){
        
        if(input[i-1]=='Y') {
            states[i] = 1;
            init_path |= 1<<(i-1);
            counts++;
        }
    }
    
    paths.push({init_path, counts});
    
    cin>>P;
    
    memset(min_costs, -1, sizeof(min_costs));
    memset(dp, -1, sizeof(dp));
    
    dp[init_path] = 0;
    for(int i=0; i<=counts; i++) min_costs[i] = 0;
    
    bfs();
    
    cout<<min_costs[P]<<endl;
    
    return 0;
}
