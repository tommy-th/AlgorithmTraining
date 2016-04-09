//
//  감시로봇.cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 4. 9..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <cstdio>
#include <algorithm>
using namespace std;

int T, N, R, L;
int robot[100005];
int result;

bool check_distance(int dis){
    bool ret = false;
    int ridx = 0;
    
    for(int i=1; i<=N; i++){
        int left = robot[i]-R;
        
        if(left < ridx){
            if(left + dis >= ridx) left = ridx;
            else left = left + dis;
        }
        else{
            if(left - dis <= ridx) left = ridx;
            else return false;
        }
        
        ridx = max(ridx, left + 2*R);
        
        if(ridx >= L){
            ret = true;
            if(result == -1) result = dis;
            else result = min(result, dis);
            return true;
        }
    }
    
    return ret;
}

void bsearch(){
    int s = 0, e = 1000000000;
    
    while(s != e){
        int mid = (s+e)/2;
        
        if(check_distance(mid)) e = mid;
        else s = mid+1;
    }
    check_distance(s);
}

int main(){
    
    scanf("%d", &T);
    
    for(int t=1; t<=T; t++){
        
        scanf("%d", &N);
        scanf("%d %d", &R, &L);
        
        for(int i=1; i<=N; i++) scanf("%d", &robot[i]);
       
        result = -1;
        
        if(2*R*N >= L) bsearch();
        
        printf("Case #%d\n%d\n", t, result);
    }
    
    
    
    return 0;
}
