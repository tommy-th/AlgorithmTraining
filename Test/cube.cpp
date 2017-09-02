//
//  cube.cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 3. 28..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
using namespace std;

#define LL long long


int T, N;
int axis[3];
int delta[3];

LL modn[3][1005];
LL result[2][1005];

void set_modn(int idx){
    int len = axis[idx]-delta[idx];
    int quoti = len / N, remain = len % N;
    
    for(int i=0; i<1005; i++){
        modn[idx][i] = 0;
    }
    
    for(int i=0; i<N; i++) modn[idx][i] += quoti;
    for(int i=0; i<remain; i++) modn[idx][i]++;
    
    quoti = delta[idx] / N, remain = delta[idx] % N;
    
    for(int i=0; i<N; i++) modn[idx][i] += quoti;
    for(int i=1; i<=remain; i++) modn[idx][i]++;
}

void set_result(){
    
    for(int i=0; i<1005; i++){
        result[0][i] = result[1][i] = 0;
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int idx = (i+j) % N;
            result[0][idx] += modn[0][i]*modn[1][j];
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int idx = (i+j) % N;
            result[1][idx] += result[0][i]*modn[2][j];
        }
    }
}

void print_result(){
    for(int i=0; i<N; i++){
        cout<<result[1][i]<<" ";
    }
    cout<<endl;
}

int main(){
    
    
    cin>>T;
    for(int t=1; t<=T; t++){
        
        for(int i=0; i<3; i++) cin >> axis[i];
        for(int i=0; i<3; i++) cin >> delta[i];
        cin>>N;
        
        for(int i=0; i<3; i++) set_modn(i);
        set_result();
        print_result();
    }
    
    
    return 0;
}
