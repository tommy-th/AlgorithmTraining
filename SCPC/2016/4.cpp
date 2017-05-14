//
//  4_2.cpp
//  AlgorithmTraining
//
//  Created by Jang on 2016. 6. 29..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 100020
#define MAXM 1000020


struct FLOW{
    int from, to, flows;
    FLOW(int from, int to, int flows) : from(from), to(to), flows(flows) {}
    
    bool operator<(const FLOW& a) const {
        return flows > a.flows;
    }
};


int visit[MAXN];
int counts[MAXN], parent[MAXN];


int T, N, M, K;

vector<FLOW> linked[MAXN];
priority_queue<FLOW> flows;


void init(){
    for(int i=0; i<MAXN; i++) linked[i].clear();
    
    memset(counts, -1, sizeof(counts));
    memset(parent, -1, sizeof(parent));
    memset(visit, 0, sizeof(visit));
}

void updateVertex(int from, int to, int cost){
    if(counts[to]<0 || cost<=counts[to]){
        if(counts[to] == cost && parent[from]>=parent[to]) return;
        parent[to] = parent[from];
        counts[to] = cost;
    }
}

void calc(){
 
    while(!flows.empty()){
        FLOW flow = flows.top(); flows.pop();
        
        updateVertex(flow.from, flow.to, flow.flows);
        
        if(visit[flow.to]) continue;
        visit[flow.to] = 1;
        
        for(int i=0; i<linked[flow.to].size(); i++){
            FLOW next = linked[flow.to][i];
            
            if(counts[next.to]<0 || next.flows+counts[next.from] <= counts[next.to]){
                flows.push(FLOW(next.from, next.to, next.flows+counts[next.from]));
            }
        }
    }
}

void printResult(){
    int nCounts = 0, pCounts = 0;
    
    for(int i=1; i<=N; i++){
        nCounts += counts[i];
        pCounts += parent[i];
    }
    cout<<nCounts<<endl;
    cout<<pCounts<<endl;
}

int main(){
    
    int shelter;
    int a, b, cost;
    
    cin>>T;
    
    for(int t=1; t<=T; t++){
        cin>>N>>M>>K;
        
        init();
        
        for(int i=1; i<=M; i++){
            cin>>a>>b>>cost;
            
            linked[a].push_back(FLOW(a, b, cost));
            linked[b].push_back(FLOW(b, a, cost));
        }
        
        for(int i=1; i<=K; i++){
            cin>>shelter;
            parent[shelter] = shelter;
            counts[shelter] = 0;
            
            for(int j=0; j<linked[shelter].size(); j++){
                visit[linked[shelter][j].from] = 1;
                flows.push(linked[shelter][j]);
            }
        }
        
        calc();
        
        cout<<"Case #"<<t<<endl;
        printResult();
    }
    
    return 0;
}