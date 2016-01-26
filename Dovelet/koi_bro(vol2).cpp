//
//  koi_bro(vol2).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 1. 26..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
int hmap[25][25][40005];
int map[25][25], ssum[25][25];
int all, dif, half;

vector<int> path;

void set_table(int y, int x, int sum){
    if(hmap[y][x][sum]) return;
    hmap[y][x][sum] = 1;
    
    if(y==0 && x== N+1){
        int temp = max(all-sum, sum)- min(all-sum,sum);
        if (temp < dif){
            dif = temp;
            half = sum;
        }
    }
    
    if(y > 0) set_table(y-1, x, sum - map[y][x]);
    if(x < N+1) set_table(y, x+1, sum + ssum[y][x+1]);
}

void search_path(int y, int x, int sum){
    if(x<=0 || y>N) return;
    if ( hmap[y][x][sum] ){
        path.push_back(y);
        search_path(y, x-1, sum - ssum[y][x]);
    }
    else {
        search_path(y+1, x, sum);
    }
}

int main(){
    
    cin >> N;
    dif = 10000000;
    
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin>>map[i][j];
            all += map[i][j];
            ssum[i][j] = ssum[i-1][j] + map[i][j];
        }
    }
    for(int i=1; i<=N; i++){
        ssum[N+1][i] = ssum[N][i];
    }
    
    set_table(N+1, 0, 0);
    search_path(0, N, half);
    
    cout<<dif<<endl;
    for(int i=N-1; i>=0; i--) cout<<N-path[i]<<" ";
    cout<<endl;
    
    return 0;
}