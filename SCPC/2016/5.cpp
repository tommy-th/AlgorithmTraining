//
//  5.cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 6. 29..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

#define LL long long

#define MAXV 105+205
#define MAXE 2*105*205

int T, N, M;

int timeSum[105];
int hashVertex[MAXV];

int src, term, eidx;
vector<int> path;
vector<int> g[MAXE];
int vertexs[MAXE], flows[MAXE];


void add_edge(int a, int b, int f){
    vertexs[eidx] = b; flows[eidx] = f; g[a].push_back(eidx); eidx++;
    vertexs[eidx] = a; flows[eidx] = 0; g[b].push_back(eidx); eidx++;
}


void init(){
    eidx=0;
    
    path.clear();
    
    for(int i=0; i<MAXE; i++){
        g[i].clear();
    }
    memset(timeSum, 0, sizeof(timeSum));
    memset(hashVertex, 0, sizeof(hashVertex));
}

int dfs(int n){
    
    hashVertex[n] = 1;
    
    for(int i=0; i<g[n].size(); i++){
        int index = g[n][i];
        int vertex = vertexs[index], flow = flows[index];
        
        if(hashVertex[vertex]) continue;
        
        if(flow>0){
            path.push_back(index);
            if (vertex == term) return 1;
            if (dfs(vertex)) return 1;
            else path.pop_back();
        }
    }
    
    return 0;
}

void set_flow(){
    
    for(int i=0; i<path.size(); i++){
        int idx = path[i], ridx = path[i]^1;
        flows[idx]--;
        flows[ridx]++;
        
    }
    path.clear();
}

void max_flow(){
    
    while(dfs(0)){
        memset(hashVertex, 0, sizeof(hashVertex));
        set_flow();
    }
}

int is_true(){
    
    for(int i=0; i<eidx; i++){
        if(flows[i] && vertexs[i]==term) return 0;
    }
    
    return 1;
}

int main(){
    
    cin>>T;
    for(int t=1; t<=T; t++){
        cin >> N >> M;
        
        term = 101+N;
        init();
        
        for(int i=1; i<=N; i++){
            int a, b, p;
            cin>>a>>b>>p;
            
            add_edge(i+100, term, p);
            for(int j=a+1; j<=b; j++) add_edge(j, i+100, 1);
        }
        
        for(int i=1; i<=M; i++){
            int a, b;
            cin>>a>>b;
            for(int i=a+1; i<=b; i++) timeSum[i]++;
        }
        
        for(int i=1; i<=100; i++) add_edge(0, i, timeSum[i]);
        
        max_flow();
        
        cout<<"Case #"<<t<<endl;
        cout<<is_true()<<endl;
    }
    
    return 0;
}
