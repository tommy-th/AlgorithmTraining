//
//  1261(알고스팟).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 6. 1..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

int N, M;

int dp[105][105];
int map[105][105];
int check[105][105];


int bfs(){
    
    queue<pair<int, int>> q;
    
    dp[1][1] = 0;
    q.push({1, 1});
    
    while (!q.empty()){
        pair<int, int> cur = q.front(); q.pop();
        int cur_val = dp[cur.first][cur.second];
        
        check[cur.first][cur.second]=0;
        
        for(int d=0; d<4; d++){
            int y = cur.first + dir[d][0], x = cur.second + dir[d][1];
            
            
            if(y>N || y<1 || x>M || x<1) continue;
            
            if(dp[y][x]==-1 || cur_val+map[y][x] < dp[y][x]){
                dp[y][x] = cur_val+map[y][x];
                
                if(check[y][x]==0){
                    check[y][x] = 1;
                    q.push({y, x});
                }
            }
        }
    }
    
    return dp[N][M];
}


int main(){
    
    cin>>M>>N;
    
    memset(dp, -1, sizeof(dp));
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            scanf("%1d", &map[i][j]);
        }
    }

    cout<< bfs() <<endl;
    
    return 0;
}
