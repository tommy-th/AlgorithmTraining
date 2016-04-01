//
//  2066(카드놀이).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 4. 2..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;


int cards[10][5];
int qhash[10000000];
double dp[10000000];

queue<vector<int>> q;


int index(vector<int> arr){
    int ret = arr[0];
    
    for(int i=1; i<9; i++){
        ret *= 5;
        ret += arr[i];
    }
    
    return ret;
}

vector<pair<int, int>> mats(vector<int> arr){
    vector<pair<int, int>> ret;
    
    for(int i=0; i<9; i++){
        if(arr[i]==0) continue;
        
        for(int j=i+1; j<9; j++){
            if(arr[j]==0) continue;
            
            else if(cards[i][arr[i]]==cards[j][arr[j]])
                ret.push_back({i, j});
        }
    }
    
    return ret;
}


void bfs(){
    
    vector<int> init;

    for(int i=0; i<9; i++) init.push_back(4);
    
    dp[index(init)] = 1.0f;
    q.push(init);
    
    while(!q.empty()){
        int aidx;
        vector<int> arr= q.front(); q.pop();
        
        vector<pair<int, int>> list = mats(arr);
        
        aidx = index(arr);
        double odds = dp[aidx];
        
        if(list.size()<=0) continue;
        
        odds = (double)(odds/list.size());
        
        for(int i=0; i<list.size(); i++){
            int a = list[i].first, b = list[i].second;
            int nidx;
            
            vector<int> next;
            
            for(int i=0; i<9; i++) next.push_back(arr[i]);
            
            --next[a]; --next[b];
            
            nidx = index(next);
            dp[nidx] += odds;

            if(qhash[nidx] == 0){
                qhash[nidx] = 1;
                q.push(next);
            }
        }
    }
}

int main(){
    
    char input[4];
    
    for(int i=0; i<9; i++) {
        for(int j=1; j<=4; j++){
            cin>>input;
            cards[i][j] = input[0] - 53;
        }
    }
    
    bfs();
    printf("%lf\n", dp[0]);

    return 0;
}
