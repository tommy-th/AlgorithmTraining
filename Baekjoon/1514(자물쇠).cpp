//
//  1514(자물쇠).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 3. 15..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int N;

int dp[110][15][15];

int password[110];
int initnums[110];

int distance(int cur, int tar) {
    int forward , backward;
    
    if( tar < cur) {
        backward = tar - cur;
        forward = 10 + backward;
    }
    else {
        forward = tar - cur;
        backward = forward - 10;
    }
    
    if(abs(forward) < abs(backward)) return forward;
    else return backward;
}

int move(int cur, int dis) {
    int ret = cur + dis;
    if(ret > 9) ret -= 10;
    if(ret < 0) ret += 10;
    return ret;
}

int counts (int dis) {
    int ret;
    if (dis < 0) dis *= -1;
    
    ret = dis/3;
    if (dis % 3 != 0) ret++;
    
    return ret;
}

void set_table(int n, int cnt, int second, int third) {
    
    if (cnt < dp[n][second][third] || dp[n][second][third] < 0)
        dp[n][second][third] = cnt;
}

void loop_disk(int n, int dis, int prev_val, int second, int third) {
    int idx = dis >= 0 ? 1 : -1;

    for(int limit = 0; limit<=abs(dis); limit++){
        for(int i=0; i<=limit; i++){
            
            int cnt = counts(dis-idx*limit) + counts(i)+ counts(limit-i) + prev_val;
            int sec_temp = move(second, idx*limit);
            int thr_temp = move(third, idx*i);
            set_table(n, cnt, sec_temp, thr_temp);
        }
    }
}

void check_point(int n, int first, int second) {
    int third = initnums[n+2];
    int dis = distance(first, password[n]);
    
    loop_disk(n+1, dis, dp[n][first][second], second, third);
    
    dis = dis < 0 ? 10 + dis : dis -10;
    
    loop_disk(n+1, dis, dp[n][first][second], second, third);
}

void search() {
    
    for(int i=1; i<=N; i++) {
        for(int j=0; j<10; j++){
            for(int k=0; k<10; k++){
                if (dp[i][j][k] < 0) continue;
                
                check_point(i, j, k);
            }
        }
    }
}

int result(){
    int ret = 999999999;
    
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            if (dp[N+1][i][j] < ret && dp[N+1][i][j] >= 0)
                ret = dp[N+1][i][j];
        }
    }
    
    return ret;
}

int main(){
    
    char input[110];
    cin >> N;
    
    memset(dp, -1, sizeof(dp));
    
    cin>> input;
    for(int i=0; i < N; i++) {
        password[i+1] = input[i] - 48;
    }
    
    cin>> input;
    for(int i=0; i< N; i++) {
        initnums[i+1] = input[i] - 48;
    }
    
    dp[1][initnums[1]][initnums[2]] = 0;
    search();
    cout<< result() <<endl;
    
    
    return 0;
}
