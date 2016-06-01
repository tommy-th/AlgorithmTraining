//
//  2146(다리만들기).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 5. 20..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

const int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

int N;
int input[105][105], map[105][105], check[105][105];


void paint(int y, int x, int c){
    if(y<=0 || y>N || x<=0 || x>N) return;
    if(map[y][x] || input[y][x]==0) return;
    
    map[y][x]=c;
    
    for(int i=0; i<4; i++)
        paint(y+dir[i][0], x+dir[i][1], c);
}

void set_map(){
    int color = 1;
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(input[i][j]==1 && map[i][j]==0){
                paint(i, j, color);
                color++;
            }
        }
    }
}

int check_connect(){
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(map[i][j]==0) continue;
            
            for(int k=0; k<4; k++){
                int ny = i+dir[k][0], nx = j+dir[k][1];
                
                if(ny<=0 || ny>N || nx<=0 || nx>N) continue;
                if(map[ny][nx]==map[i][j]) continue;
                if(map[ny][nx]) return 1;
                if(check[ny][nx] != map[i][j] && check[ny][nx]) return 2;
                
                check[ny][nx] = map[i][j];
            }
        }
    }
    
    return 0;
}

void make_bridge(){
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(check[i][j]) map[i][j] = check[i][j];
        }
    }
}

void print_map(){
    cout<<endl;
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<endl;
    }
}

int min_bridge(){
    int lc, ret = 0;
    
    while(1){

//        print_map();
        
        lc = check_connect();
        
        if(lc){
            ret += (lc-1);
            break;
        }
        make_bridge();
        ret += 2;
    }

    return ret;
}

int min_bridge2(){
    
    int temp, ret = 1000;
    
    for(int y1=1; y1<=N; y1++){
        for(int x1=1; x1<=N; x1++){
            if(map[y1][x1]==0) continue;
            
            for(int y2=1; y2<=N; y2++){
                for(int x2=1; x2<=N; x2++){
                    if(map[y2][x2]==0 || map[y2][x2] == map[y1][x1]) continue;
                    
                    temp = abs(y2-y1) + abs(x2-x1) - 1;
                    ret = ret > temp ? temp : ret;
                }
            }
        }
    }
    
    return ret;
}


int main(){
    
    cin>>N;
    
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++) cin>>input[i][j];
    
    set_map();
    
    cout<<min_bridge2()<<endl;
    cout<<min_bridge()<<endl;
    
    return 0;
}
