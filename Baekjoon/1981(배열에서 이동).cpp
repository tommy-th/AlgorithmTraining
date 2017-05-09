//
//  1981(배열에서 이동).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 10. 1..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;


const int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

int N;
int result_val;

int check[105][105];
int map[105][105];
int dp[105][105][205];


void search_point(int y, int x, int min_p, int max_p){
    
    int min_c = min_p < map[y][x] ? min_p : map[y][x];
    int max_c = max_p > map[y][x] ? max_p : map[y][x];
    int temp = max_c - min_c;
    
    if(check[y][x]) return;
    if(y<1 || x<1 || x>N || y>N) return;
    if(temp >= result_val) return;
    if(dp[y][x][max_c] >= min_c) return;
  
    
    if (y==N && x==N){
        result_val =  temp < result_val ? temp : result_val;
        return;
    }
    
    dp[y][x][max_c] = min_c;
    check[y][x] = 1;
    
    for(int i=0; i<4; i++){
        search_point(y+dir[i][0], x+dir[i][1], min_c, max_c);
    }
    check[y][x] = 0;
}

int main(){
    
    cin>>N;
    
    result_val = 200;
    memset(dp, -1, sizeof(dp));
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin>>map[i][j];
        }
    }
    
    search_point(1, 1, 200, 0);
    
    cout<<result_val<<endl;
    
    return 0;
}
