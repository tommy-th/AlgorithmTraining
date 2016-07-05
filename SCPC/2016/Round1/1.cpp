//
//  1.cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 6. 29..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#define LL long long int

int T, K;

int D[10000000], check[1000];

int func(int n){
    if(n==1) return 0;
    if(D[n]) return D[n];
    
    if(n%2==0) D[n] = func(n/2)+1;
    else D[n] = func(n*3+1)+1;

    return D[n];
}

int min_ret(){
    for(int i=1; i<=2000; i++){
        if(D[i]==K) return i;
    }
    return 0;
}

LL exp(int n){
    LL ret = 1;
    
    for(int i=1; i<=n; i++){
        ret *= 2;
    }
    
    return ret;
}


int main(){
    
    for(int i=1; i<=2000; i++) func(i);
    
    for(int i=0; i<=2000; i++){
        if(D[i]<=63) check[D[i]] = 1;
    }
    
    for(int i=0; i<=63; i++){
        if(check[i]==0) cout<<i<<endl;
    }
    
    cin>>T;
    
    for(int t=1; t<=T; t++){
        cin>>K;
        
        cout<<"Case #"<<t<<endl;
        cout<<min_ret()<<" ";
        
        if(K<63){
            cout<<exp(K)<<endl;
        }
        else{
            cout<<"9223372036854775808"<<endl;
        }
    }
    
    return 0;
}
