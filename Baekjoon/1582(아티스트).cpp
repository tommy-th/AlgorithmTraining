//
//  1582(아티스트).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 3. 26..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;

int N, M, K;

int map_size;
int map[105][105];
int once[105][105][105];            // [n][a][b] -> n번 째 줄의 a, b 구간에 한 번 칠했을 때 최대 값
int max_horizon[105][105][105];     // [n][k][b] -> n번 째 줄의 1, b 구간에 k 번 칠했을 때 최대 값

int vidx;
int max_vertical[3005];

void set_once(int n){
    int swt, wcnt, bcnt;
    
    for (int i=1; i<=map[n][0]; i++){
        swt = -1;
        wcnt = bcnt = 0;
        
        for(int j=i; j<=map[n][0]; j++){
            if(swt<0) wcnt += map[n][j];
            else bcnt += map[n][j];
            
            once[n][i][j] = max(wcnt, bcnt);
            if(i==1) max_horizon[n][1][j] = once[n][i][j];
            
            swt *= -1;
        }
    }
}

void set_horizon(int n){
    set_once(n);
    
    for (int dep=2; dep<=map[n][0]; dep++){
        
        max_horizon[n][dep][1] = once[n][1][1];
        
        for(int i=2; i<=map[n][0]; i++){
            for(int j=2; j<=i; j++){
                int temp = max_horizon[n][dep-1][j-1] + once[n][j][i];
                max_horizon[n][dep][i] = max(max_horizon[n][dep][i], temp);
            }
        }
    }
}

void set_vertical(int n){
    int len = map[n][0];
    
    vidx += len;
    if(vidx>3000) vidx = 3000;
    
    for(int i=vidx; i>=1; i--){
        for(int j=1; j<=len; j++){
            if(j>i) break;
            int temp = max_horizon[n][j][len] + max_vertical[i-j];
            max_vertical[i] = max(max_vertical[i], temp);
        }
    }
}

int main(){
    
    int cnt;
    char color;
    char input[105];
    
    cin>>N>>M>>K;
    
    for (int i=1; i<=N; i++){
        cin>>&input[1];
        color = input[1];
        
        cnt = 0;
        for(int j=1; j<=M; j++){
            if(color != input[j]){
                color = input[j];
                map[i][0]++;
                map[i][map[i][0]] = cnt;
                map_size += cnt;
                cnt = 0;
            }
            cnt++;
        }
        map[i][0]++;
        map[i][map[i][0]] = cnt;
        map_size += cnt;
    }
    
    for (int i=1; i<=N; i++) set_horizon(i);
    for (int i=1; i<=N; i++) set_vertical(i);
    
    if(K > vidx) K = vidx;
    
    cout<< map_size - max_vertical[K]<<endl;
    
    return 0;
}
