//
//  2500(복불복).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 2. 4..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

#define MOD 42043

int N, K, T;
int D[50][1005], result[1005];

void calc_next(int n){
    for (int i = 0; i <= K; i++){
        for (int j = 0; i + j <= K; j++){
            D[n][i + j] += D[n-1][i] * D[n-1][j];
            D[n][i + j] %= MOD;
        }
    }
}

void calc_result(int n){
    memset(result, 0, sizeof(result));
    
    for (int i = 0; i <= K; i++){
        for (int j = 0; i + j <= K; j++){
            result[i + j] += D[0][i] * D[n][j];
            result[i + j] %= MOD;
        }
    }
    for(int i=0; i<=K; i++) D[0][i] = result[i];
}

void init_result(int n) {
    for (int i = 0; i <= K; i++) {
        result[i] = D[0][i] = D[n][i];
    }
}

void set_table(){
    
    int n = N, idx = 1, on = 0;
    
    while(n) {
        if (n&0x01) {
            if (on)
                calc_result(idx);
            else {
                on=1;
                init_result(idx);
            }
        }
        n>>=1;
        calc_next(++idx);
    }
}

int main(){
    int num, sum = 0;
    
    cin >> N >> K >> T;
    
    for (int i = 1; i <= T; i++){
        cin >> num;
        D[1][num]++;
    }
    
    set_table();
    
    for (int i = 0; i <= K; i++){
        sum += result[i];
        sum %= MOD;
    }
    
    cout << sum << endl;
    
    return 0;
}