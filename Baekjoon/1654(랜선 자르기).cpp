//
//  1654(랜선 자르기).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 5. 28..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//


#include <iostream>
#include <algorithm>
using namespace std;

#define LL long long

int K, N;

LL lines[10005], result;

int check(LL len){
    LL count = 0;
    
    for(int i=1; i<=K; i++){
        count += lines[i]/len;
        
        if(count>=N){
            result = max(result, len);
            return 1;
        }
    }
    
    return 0;
}

void bsearch(){
    LL min = 0, max = 2147483650;
    
    while(min < max){
        LL mid = (min+max)/2;
        
        if(check(mid)) min = mid+1;
        else max = mid-1;
    }
    check(min);
}

int main(){
    
    cin>>K>>N;
    
    for(int i=1; i<=K; i++) cin>>lines[i];
    
    bsearch();
    
    cout<<result<<endl;
    
    return 0;
}