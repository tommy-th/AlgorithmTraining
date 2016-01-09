//
//  bfs_test.cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 1. 8..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

typedef struct __point {
    int x, y;
    __point(){}
    __point(int y, int x) :  y(y), x(x) {}
} point;

int T, N, hx, hy;
int dir[4][2] = { {0, 1}, {1,0}, {-1,0}, {0,-1}};
int map[105][105], hmap[105][105];

queue<point> q = queue<point>();

void searchPoint(int y, int x, int sum){
    if( y<0 || x<0 || y>N+1 || x>N+1) return;
    if(hmap[y][x] >= 0 && sum >= hmap[y][x]) return;
    hmap[y][x] = sum;
    q.push(point(y, x));
}

void setHash(){
    memset(hmap, -1, sizeof(hmap));
    
    for(int i=0; i<=N; i++){
        hmap[i][N+1] = hmap[i][0] = 0;
        q.push(point(i, N+1));
        q.push(point(i, 0));
    }
    for(int j=0; j<=N; j++){
        hmap[N+1][j] = hmap[0][j] = 0;
        q.push(point(N+1, j));
        q.push(point(0, j));
    }
}

void startHiking(){
    int x, y, nx, ny, psum;
    setHash();
    
    while( !q.empty()){
        point cur = q.front();
        y = cur.y, x = cur.x;
        q.pop();
        
        for(int i=0; i<4; i++) {
            ny = y+dir[i][0], nx = x+dir[i][1];
    
            if(map [ny][nx] > map[y][x])
                psum = (map[ny][nx] - map[y][x]) * (map[ny][nx] - map[y][x]);
            else
                psum =map[y][x] - map[ny][nx];
            searchPoint(ny, nx, hmap[y][x] + psum);
        }
    }
}

int main(){
    
    cin>> T;
    for(int t=1; t<=T; t++){
        cin>>N;
        cin>>hy>>hx;
        memset(map, 0, sizeof(map));
        
        for(int i=1; i<=N; i++){
            for(int j=1; j<=N; j++) cin>>map[i][j];
        }
        
        startHiking();

        cout<<"#testcase"<<t<<endl;
        cout<<hmap[hy][hx]<<endl;
    }
    
    return 0;
}