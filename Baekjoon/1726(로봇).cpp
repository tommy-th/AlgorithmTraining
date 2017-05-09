//
//  1726(로봇).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 10. 15..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#define INF 1000000

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 동쪽이 1, 서쪽이 2, 남쪽이 3, 북쪽이 4
const int dir[5][2] = {{0,0}, {0,1}, {0,-1}, {1,0}, {-1,0}};
const int rot[5][3] = {{0,0,0}, {3,4,2}, {3,4,1}, {1,2,4}, {1,2,3}};

int N, M;
int map[105][105];
int dp[105][105][5];
int check[105][105][5];

int sy, sx, sd, ey, ex, ed;

void bfs(){
    queue<pair<pair<int, int>, int>> q;
    
    dp[sy][sx][sd] = 0;
    check[sy][sx][sd] = 1;
    q.push({make_pair(sy, sx), sd});
    
    while(!q.empty()){
        pair<pair<int, int>, int> cur = q.front(); q.pop();
        
        int cy=cur.first.first, cx=cur.first.second, cd=cur.second;
        check[cy][cx][cd] = 0;
        
        // 로봇 이동 명령
        for(int len=1; len<=3; len++){
            int ny=cy+len*dir[cd][0];
            int nx=cx+len*dir[cd][1];
            int nd=cd;
            
            if(ny>N||nx>M||ny<1||nx<1) break;
            if(map[ny][nx]) break;
            
            int count = dp[cy][cx][cd] + 1;

            if(count < dp[ny][nx][nd]){
                dp[ny][nx][nd] = count;
                
                if(check[ny][nx][nd]==0){
                    check[ny][nx][nd] = 1;
                    q.push({make_pair(ny, nx), nd});
                }
            }
        }
        
        // 로봇 회전 명령
        for(int r=0; r<3; r++){
            int ny=cy, nx=cx, nd = rot[cd][r];
            int count = dp[cy][cx][cd]+1;
            
            if(r==2)count++;
            
            if(count < dp[ny][nx][nd]){
                dp[ny][nx][nd] = count;
                
                if(check[ny][nx][nd]==0){
                    check[ny][nx][nd] = 1;
                    q.push({make_pair(ny, nx), nd});
                }
            }
        }
    }
    
}


int main(){

    cin>>N>>M;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            cin>>map[i][j];
        }
    }
    cin>>sy>>sx>>sd;
    cin>>ey>>ex>>ed;
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            for(int k=1; k<=4; k++)
                dp[i][j][k] = INF;
        }
    }
    
    bfs();
    
    cout<<dp[ey][ex][ed]<<endl;
    
    return 0;
}
