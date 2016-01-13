//
//  11493 - A(SPFA).cpp
//  AlgorithmTraining
//
//  Created by JangTaehwan on 2016. 1. 13..
//  Copyright © 2016년 JangTaehwan. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 1024*1024
#define MAXV 505
#define MAXE 505*505*3

int N, M, T;
int L[MAXV], R[MAXV], lidx, ridx, tidx, eidx;
int dis[MAXV][MAXV];

vector<int> ng[MAXV], vg[MAXE];
int vertexs[MAXE], flows[MAXE], costs[MAXE];
vector<int> path;

void bfs(int n) {
    int inque[MAXV] = { 0, };
    queue<int> q;
    
    for(int i=1; i<=N; i++) dis[n][i] = INF;
    dis[n][n] = 0; q.push(n);
    
    while(!q.empty()) {
        int cur = q.front(); q.pop();
        inque[cur] = 0;
        for (int i=0; i<ng[cur].size(); i++) {
            int next = ng[cur][i];
            if(dis[n][next] < INF) continue;
            dis[n][next] = dis[n][cur] +1;
            if (!inque[next]){
                inque[next] = 1;
                q.push(next);
            }
        }
    }
}

void add_edge(int a, int b, int flow, int cost){

    vertexs[eidx] = b; flows[eidx] = flow; costs[eidx] = cost; vg[a].push_back(eidx); eidx++;
    vertexs[eidx] = a; flows[eidx] = 0; costs[eidx] = -cost; vg[b].push_back(eidx); eidx++;
}

int spfa(){
    vector<int> inque(tidx+1, 0), dp(tidx+1, INF), from(tidx+1, -1);
    queue<int> q;
    path.clear();
    
    q.push(0); inque[0] = 1; dp[0] = 0;
    while(!q.empty()){
        int cur = q.front(); q.pop();
        inque[cur] = 0;
        for(int i=0; i<vg[cur].size(); i++){
            int idx = vg[cur][i];
            int next = vertexs[idx];
            if (!flows[idx] || dp[next] <= dp[cur] + costs[idx]) continue;
            dp[next] = dp[cur] + costs[idx];
            from[next] = idx;
            if (!inque[next]) {
                inque[next] = 1;
                q.push(next);
            }
        }
    }
    
    if (from[tidx] < 0) return 0;
    
    for(int i = tidx; i; i = vertexs[from[i]^1]) path.push_back(from[i]);
    
    return 1;
}

int main(){
    int a, b, result;
    
    cin>>T;
    for(int t=1; t<=T; t++){
        cin>>N>>M;
        
        result = 0;
        for(int i=0; i<=N; i++) ng[i].clear();
        
        for(int i=1; i<=M; i++){
            cin>> a>> b;
            ng[a].push_back(b);
            ng[b].push_back(a);
        }
        
        for(int i=1; i<=N; i++) cin >> L[i];
        for(int i=1; i<=N; i++) cin >> R[i];
        
        eidx = lidx = ridx = 0;
        for(int i=1; i<=N; i++) {
            if(L[i] && R[i]) L[i] = R[i] = 0;
            else if(L[i]) L[i] = ++lidx;
            else if(R[i]) R[i] = ++ridx;
        }
        
        for(int i=1; i<=N; i++) if(L[i]) bfs(i);

        tidx = lidx + ridx + 1;
        
        for(int i=0; i<=tidx; i++) vg[i].clear();
        for(int i=1; i<=lidx; i++) add_edge(0, i, 1, 0);
        for(int j=1; j<=ridx; j++) add_edge(j + lidx, tidx, 1, 0);
        for(int i=1; i<=N; i++) if (L[i]) {
            for(int j=1; j<=N; j++) if (R[j]) {
                add_edge(L[i], lidx + R[j], 1, dis[i][j]);
            }
        }
        
        while(spfa()){
            for (int i=0; i<path.size(); i++){
                int idx = path[i];
                result += costs[idx];
                flows[idx^1] +=1;
                flows[idx] -= 1;
            }
        }
        
        cout<<result<<endl;
    }
    
    return 0;
}
