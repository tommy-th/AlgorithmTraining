//
//  윤목.cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 4. 9..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
using namespace std;

#define LL long long

LL result[6];
LL T, A;
LL up, down;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a%b) : a;
}

void divide(){
    LL g = gcd(up, down);
    up /= g;
    down /= g;
}


void calc(){
    
    up += (down*A);
    
    for(int i=1; i<=5; i++){
        LL def = up - (down*i);
        LL idx = def > 0 ? 1 : -1;
        
        if (def*idx >= down) continue;
        else{
            result[i] = down - def*idx;
            result[i + idx] = def*idx;
            break;
        }
    }
}


int main(){
    
    char input[15];
    
    cin>>T;
    for(int i=1; i<=T; i++){
        
        cin>>input;
        
        up=0, down=1;
        for(int j=1; j<=5;j++) result[j]=0;
        
        A = input[0]-48;
        
        for(int j=2; j<strlen(input);j++){
            up *=10;
            down*=10;
            up += (LL)(input[j]-48);
        }
        
        divide();
        calc();
        cout<<"Case #"<<i<<endl;
        for(int j=1; j<=5; j++) cout<<result[j]<<" ";
        cout<<endl;
    }
    
    
    
    return 0;
}
