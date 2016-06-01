//
//  11375(열혈강호).cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 5. 6..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

#define MAXV 1005
#define MAXE 2004005

int N, M;

int vertexs[MAXE], flows[MAXE], gidx;
vector<int> g[MAXV];

void insert_edge(int s, int e){
    vertexs[gidx] = e; flows[gidx] = 1; g[0].push_back(gidx); gidx++;
    vertexs[gidx] = s; flows[gidx] = 0; g[0].push_back(gidx); gidx++;
}

int main(){
    int num, job;
    
    cin>>N>>M;
    
    for(int i=1; i<=N; i++){
        insert_edge(0, i);
    }
    
    for(int i=1; i<=N; i++){
        cin>>num;
        
        for(int j=1; j<=num; j++){
            cin>>job;
            
            insert_edge(i, job);
        }
    }
    
    for(int i=1; i<=M; i++){
        insert_edge(0, i);
    }
    
    
    return 0;
}
